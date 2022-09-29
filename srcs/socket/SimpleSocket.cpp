#include "SimpleSocket.hpp"

// DEFAULT CONTRUCTOR

SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port,
		u_long interface, int backlog) : backlog(backlog)
{
   //Define address structure
   this->address.sin_family = domain;
   this->address.sin_port = htons(port);
   this->address.sin_addr.s_addr = htonl(interface);
	
   // Establish socket
	this->sock_fd = socket(domain, service, protocol);
	test_connection(this->sock_fd);

	// Bind
	this->connection = connect_to_network();
	test_connection(this->connection);

	// Listen
	this->listening = start_listening();
	test_connection(this->listening);
}

// Test connection function
void	SimpleSocket::test_connection(int item_to_test)
{
	// confirm that the socket or connection has been properly established
	if (item_to_test < 0)
	{
		perror("Fialed to connect...");
		exit(EXIT_FAILURE);
	}
}

// Bind function
int		SimpleSocket::connect_to_network(void)
{
	return (bind(this->sock_fd, (struct sockaddr *)&this->address,
				sizeof(this->address)));
}

// listening function
int		SimpleSocket::start_listening(void)
{
	return(listen(this->sock_fd, this->backlog));
}

// Getter functions

struct sockaddr_in SimpleSocket::get_address(void)
{
	return (this->address);
}

int		SimpleSocket::get_sock_fd(void)
{
	return (this->sock_fd);
}

int		SimpleSocket::get_connection(void)
{
	return(this->connection);
}

// Setter fucntions
void	SimpleSocket::set_address(struct sockaddr_in address)
{
	this->address = address;
	return ;
}

void	SimpleSocket::set_sock_fd(int sock_fd)
{
	this->sock_fd = sock_fd;
	return ;
}

void	SimpleSocket::set_connection(int connection)
{
	this->connection = connection;
	return ;
}

