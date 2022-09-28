#include "SimpleSocket.hpp"

// DEFAULT CONTRUCTOR

SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, u_long interface)
{
   //Define address structure
   this->address.sin_family = domain;
   this->address.sin_port = htons(port);
   this->address.sin_addr.s_addr = htonl(interface);
	
   // Establish socket
	this->sock_fd = socket(domain, service, protocol);
	test_connection(sock_fd);
}

// Test connection virtual function
void SimpleSocket::test_connection(int item_to_test)
{
	// confirmst that the socket or connection has been properly established
	if (item_to_test < 0)
	{
		perror("Fialed to connect...");
		exit(EXIT_FAILURE);
	}
}

// Getter functions

struct sockaddr_in SimpleSocket::get_address(void)
{
	return (this->address);
}

int	SimpleSocket::get_sock_fd(void)
{
	return (this->sock_fd);
}

int SimpleSocket::get_connection(void)
{
	return(this->connection);
}

// Setter fucntions
void SimpleSocket::set_address(struct sockaddr_in address)
{
	this->address = address;
	return ;
}

void SimpleSocket::set_sock_fd(int sock_fd)
{
	this->sock_fd = sock_fd;
	return ;
}

void SimpleSocket::set_connection(int connection)
{
	this->connection = connection;
	return ;
}

