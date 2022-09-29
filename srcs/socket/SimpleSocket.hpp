#ifndef SIMPLESOCKET_HPP
#define SIMPLESOCKET_HPP

#include <cstdio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

class SimpleSocket
{
	private:
		struct sockaddr_in	address;
		int 				sock_fd;
		int 				connection;
		int					listening;
		int					backlog;

	public:
		SimpleSocket(int domain, int service, int protocol, int port,
				u_long interface, int backlog);

		// check return value
		void 		test_connection(int);

		// Bind fuction
		int			connect_to_network(void);
		
		// listening function
		int			start_listening(void);
	
		// getter functions
		struct sockaddr_in	get_address();
		int 				get_sock_fd();
		int 				get_connection();

		//Setter fucntions
		void				set_address(struct sockaddr_in address);
		void				set_sock_fd(int sock_fd);
		void				set_connection(int connection);
};

#endif
