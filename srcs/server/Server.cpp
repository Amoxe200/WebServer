#include "Server.hpp"

Server::Server(int domain, int service, int protocol, int port,
		u_long interface, int backlog)
{
	creatSocket(domain, service, protocol, port, interface, backlog);
	initialize_current_sockets();
	launch();
}

void	Server::creatSocket(int domain, int service, int protocol,
		int port, u_long interface, int backlog)
{
	this->socket = new SimpleSocket(domain, service, protocol, port,
			interface, backlog);
	this->server_socket = this->socket->get_server_sock();
}

void	Server::initialize_current_sockets(void)
{
	FD_ZERO(&this->current_sockets);
	FD_SET(this->server_socket, &this->current_sockets);
}

bool	Server::check_header(void)
{
	for(size_t i = 0; i < this->request.size() - 1; i++)
    {
        if (this->request[i] == '\n' && this->request[i + 1] == '\n')
        {
            this->request[i + 1] = '$';
			return (true);
		}
    }
	return (false);
}

void	Server::readSocket(int fd)
{

	std::string		buf;
	char			*sendRequest;
	char			*body = NULL;
	// read the socket
	recv(fd, &buf, 1024, 0);
	if (this->request.empty())
		this->request = buf;
	else
		this->request += buf;
	bzero(&buf, 1024);
	if (check_header())
	{
		sendRequest = strtok(&this->request[0], "$");
		body = strtok(NULL, "$");
		ParsingRequest *parsingRequest = new ParsingRequest(sendRequest);
	}
	if (body != NULL)
	{
		std::cout << "BODY : " << strlen(body) << std::endl;
	}
}

void	Server::selecter(void)
{
	// because select is destructive
	this->read_sockets = this->current_sockets;
	this->write_sockets = this->current_sockets;
	int maxFd;

	maxFd = (!this->vClient_socket.empty()) ? this->vClient_socket.back() : this->server_socket;
	maxFd++;

	if (select(maxFd, &this->read_sockets, &this->write_sockets, NULL, NULL) < 0)
	{
		perror("select error");
		exit(EXIT_FAILURE);
	}
}

void	Server::accepter(void)
{
	struct sockaddr_in	address = this->socket->get_address();
	int			addrlen = sizeof(this->socket->get_address());
	
	if (FD_ISSET(this->server_socket, &this->read_sockets))
	{
		std::cout << "i was here" << std::endl;
		this->vClient_socket.push_back(accept(this->server_socket,
		(struct sockaddr *)&address, (socklen_t *)&addrlen));
		FD_SET(this->vClient_socket.back(), &this->current_sockets);
	}
}

void	Server::responder(int index)
{
	std::string rep = "HTTP/1.1  200 OK\r\nContent-Type: text/html\r\nContent-Length: 37\r\n\r\n<html><body><h2>ok</h2></body></html>";
	send(vClient_socket[index], rep.c_str(), rep.length(), 0);
	close(vClient_socket[index]);
	FD_CLR(vClient_socket[index], &this->current_sockets);
	vClient_socket.erase(vClient_socket.begin() + index);
}

void	Server::launch(void)
{
	while(true)
	{
		std::cout << "============ WAITING 	=============" << std::endl;
		selecter();
		accepter();
		for(size_t i = 0; i < vClient_socket.size(); i++)
		{
			if (FD_ISSET(vClient_socket[i], &this->read_sockets))
			{
				readSocket(vClient_socket[i]);
			}
			if (FD_ISSET(vClient_socket[i], &this->write_sockets))
			{
				responder(i);
				break ;
			}
		}
		std::cout << "============  DONE 	=============" << std::endl;
	}
}