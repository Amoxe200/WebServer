#include "BindingSocket.hpp"

BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface)
: SimpleSocket(domain, service, protocol, port, interface)
{
	std::cout << "Default Constructor BindingSocket Called" << std::endl;
	set_connection(connect_to_network(get_sock_fd(), get_address()));
	test_connection(get_connection());
	return ;
}

int	BindingSocket::connect_to_network(int sock_fd, struct sockaddr_in address)
{
	return (bind(sock_fd, (struct sockaddr *)&address, sizeof(address)));
}
