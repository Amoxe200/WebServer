#ifndef BINDINGSOCKET_HPP
#define BINDINGSOCKET_HPP

#include <stdio.h>

#include "SimpleSocket.hpp"

class BindingSocket : public SimpleSocket
{
	public:
		BindingSocket(int domain, int service, int protocol, int port, u_long interface);
		int	connect_to_network(int sock_fd, struct sockaddr_in address);
};

#endif
