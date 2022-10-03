#ifndef SERVER_HPP
#define SERVER_HPP

#include <unistd.h>
#include <sys/select.h>
#include "../socket/SimpleSocket.hpp"

class Server
{
	private:
		SimpleSocket *	socket;
		int		client_socket;
		int		server_socket;
		fd_set		ready_sockets;
		fd_set		current_sockets;
	//	std::string			buffer[30000];
	public:
		Server(int domain, int service, int protocol, int port,
				u_long interface, int backlog);
		
		void	creatSocket(int domain, int service, int protocol, int port,
					u_long interface, int backlog);
		void	initialize_current_sockets(void);
		void	selecter(void);
		void	handler(void);
		void	responder(void);
		void	launch(void);
		
};


#endif
