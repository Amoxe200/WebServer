#ifndef SIMPLESOCKET_HPP
#define SIMPLESOCKET_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

class SimpleSocket
{
	private:
		struct sockaddr_in address;
		int sock_fd;
		int connection;
	public:
		SimpleSocket(int domain, int service, int protocol, int port, u_long interface);
		virtual int connect_to_ntwork(int sock_fd, struct sockaddr_in address) = 0;
		void test_connection(int);

		// getter functions
		struct sockaddr_in get_address();
		int get_sock_fd();
		int get_connection();
		//Setter fucntions
		void	set_address(struct sockaddr_in address);
		void	set_sock_fd(int sock_fd);
		void	set_connection(int connection);
};

#endif
