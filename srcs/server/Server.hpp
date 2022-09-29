#ifndef SERVER_HPP
#define SERVER_HPP

#include <unistd.h>

#include "../socket/SimpleSocket.hpp"

class Server
{
	private:
		SimpleSocket *	socket;
		int				new_socket;
	//	std::string			buffer[30000];
	public:
		Server(int domain, int service, int protocol, int port,
				u_long interface, int backlog);
		
		void	creatSocket(int domain, int service, int protocol, int port,
					u_long interface, int backlog);
		void	accepter();
		void	handler();
		void	responder();
		void	launch();
		
};


#endif
