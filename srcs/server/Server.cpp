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
	FD_SET(this->socket->get_server_sock(), &this->current_sockets);
}

void	Server::selecter(void)
{
	struct sockaddr_in	address = this->socket->get_address();
	int			addrlen = sizeof(this->socket->get_address());

	// because select is destructive
	this->ready_sockets = this->current_sockets;

	if (select(4, &ready_sockets, NULL, NULL, NULL) < 0)
	{
		std::cout << "here \n";
		perror("select error");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < FD_SETSIZE; i++)
	{
		if (FD_ISSET(i, &ready_sockets))
		{
			if (i == server_socket)
			{
				//this is a new connection}
				this->client_socket = accept(this->server_socket,
				(struct sockaddr *)&address, (socklen_t *)&addrlen);
				std::cout << "accept -> " << this->client_socket << std::endl;
				FD_SET(this->client_socket, &this->current_sockets);
			}
			else
				handler();
		}
	}
}

void	Server::handler(void)
{	
	int 		n;
	uint8_t		recvline[4096+1];
	std::string str[4096];

	std::cout << "--------\n";
	while (( n = recv(this->client_socket, str, 4096 - 1, 0)) > 0)
	{
		std::cout << str << std::endl;
		fprintf(stdout, "\n%s\n", recvline);
		if (recvline[n-1] == '\n')
			break ;
		memset(recvline, 0, 4096);
	}
}

void	Server::responder(void)
{
	char *hello = (char *)"Hello from server";
	write(this->client_socket, hello, strlen(hello));
	close(this->client_socket);
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
