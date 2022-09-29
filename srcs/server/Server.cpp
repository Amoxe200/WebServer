#include "Server.hpp"

Server::Server(int domain, int service, int protocol, int port,
		u_long interface, int backlog)
{
	creatSocket(domain, service, protocol, port, interface, backlog);
	launch();
}

void	Server::creatSocket(int domain, int service, int protocol,
		int port, u_long interface, int backlog)
{
	this->socket = new SimpleSocket(domain, service, protocol, port,
			interface, backlog);
}

void	Server::accepter()
{
	uint8_t				recvline[4096+1];
	int					n;	

	struct sockaddr_in	address = this->socket->get_address();
	int		addrlen = sizeof(this->socket->get_address());
	int		sock_fd = this->socket->get_sock_fd();

	this->new_socket = accept(sock_fd, (struct sockaddr *)&address,
			(socklen_t *)&addrlen);

	while(( n = read(this->new_socket, recvline, 4096 - 1)) > 0)
	{
		fprintf(stdout, "\n%s\n", recvline);
		if (recvline[n-1] == '\n')
			break ;
		memset(recvline, 0, 4096);
	}
}

void	Server::handler()
{
	//std::cout << this->buffer << std::endl;
}

void	Server::responder()
{
	char *hello = (char *)"Hello from server";
	write(this->new_socket, hello, strlen(hello));
	close(this->new_socket);
}

void	Server::launch()
{
	while(true)
	{
		std::cout << "============ WAITING 	=============" << std::endl;
		accepter();
		handler();
		responder();
		std::cout << "============  DONE 	=============" << std::endl;
	}
}
