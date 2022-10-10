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

void	Server::selecter(void)
{
	struct sockaddr_in	address = this->socket->get_address();
	int			addrlen = sizeof(this->socket->get_address());

	// because select is destructive
	this->read_sockets = this->current_sockets;
	this->write_sockets = this->current_sockets;

	if (select(FD_SETSIZE, &this->read_sockets, &this->write_sockets, NULL, NULL) < 0)
	{
		perror("select error");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < FD_SETSIZE; i++)
	{
		if (FD_ISSET(i, &read_sockets))
		{
			if (i == server_socket)
			{
				this->client_socket = accept(this->server_socket,
				(struct sockaddr *)&address, (socklen_t *)&addrlen);
				FD_SET(this->client_socket, &this->current_sockets);
			}
			else
			{
				std::cout << "HERE222222\n" << std::endl;
				this->client_socket = i;
				handler();
			}
		}
	}
}

void	Server::handler(void)
{	
	int 		n;
	uint8_t		recvline[4096+1];

	std::cout << "--------\n";
	while (( n = recv(this->client_socket, recvline, 4096 - 1, 0)) > 0)
	{
		fprintf(stdout, "\n%s\n", recvline);
		if (recvline[n-1] == '\n')
			break ;
		memset(recvline, 0, 4096);
	}
}

void	Server::responder(void)
{
	std::string rep = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 37\r\n\r\n<html><body><h2>ok</h2></body></html>";
	send(this->client_socket, &rep, rep.length(), 0);
	close(this->client_socket);
	FD_CLR(this->client_socket, &this->current_sockets);
}

void	Server::launch(void)
{
	while(true)
	{
		std::cout << "============ WAITING 	=============" << std::endl;
		selecter();
		//handler();
		responder();
		std::cout << "============  DONE 	=============" << std::endl;
	}
}
