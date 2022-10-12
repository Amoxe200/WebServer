#include "Server.hpp"

Server::Server(int domain, int service, int protocol, int port,
		u_long interface, int backlog)
{
	this->client_socket = -1;
	this->max_fd = 0;
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
	if (this->server_socket > this->max_fd)
		this->max_fd = this->server_socket;
}

void	Server::initialize_current_sockets(void)
{
	FD_ZERO(&this->current_sockets);
	FD_SET(this->socket->get_server_sock(), &this->current_sockets);
}

void	Server::selecter(void)
{
	struct sockaddr_in	address = this->socket->get_address();
	int			addrlen = sizeof(this->socket->get_address());

	// because select is destructive
	this->ready_sockets = this->current_sockets;

	if (select(this->max_fd + 1, &ready_sockets, NULL, NULL, NULL) < 0)
	{
		perror("select error");
		exit(EXIT_FAILURE);
	}
	std::cout << "SETSIZE : " << this->max_fd << std::endl;
	for(int i = 0; i < this->max_fd + 1; i++)
	{
		std::cout << "checking for socket connection" << std::endl;
		if (FD_ISSET(i, &ready_sockets))
		{
			if (i == server_socket)
			{
				//this is a new connection}
				std::cout << "Trying to accept new client" << std::endl;
				this->client_socket = accept(this->server_socket,
				(struct sockaddr *)&address, (socklen_t *)&addrlen);
				std::cout << "new client " << this->client_socket << std::endl;
				if (this->client_socket != -1)
					FD_SET(this->client_socket, &this->current_sockets);
				if (this->client_socket > this->max_fd)
					this->max_fd = this->client_socket;
			}
			else
			{
				std::cout <<"print REquest" << std::endl;
				handler(i);
			}
		}
	}
}

void	Server::handler(int i)
{	
	int 		n;
	uint8_t		recvline[4096+1];
	//std::string str[4096];

	std::cout << "--------\n";
	while (( n = read(i, recvline, 4096 - 1)) > 0)
	{
	//	std::cout << str << std::endl;
		fprintf(stdout, "\n%s\n", recvline);
		if (recvline[n-1] == '\n')
			break ;
		memset(recvline, 0, 4096);
	}
}

void	Server::responder(void)
{
	std::cout << "client socket: " << this->client_socket << std::endl;
	char *hello = (char *)"HTTP/1.1 200 OK\nDate: Mon, 27 Jul 2009 12:28:53 GMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Length: 88\nContent-Type: text/html\nConnection: Closed";
	write(this->client_socket, hello, strlen(hello));
	close(this->client_socket);
	FD_CLR(this->client_socket, &this->current_sockets);
	this->client_socket = -1;
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
