#ifndef SERVER_HPP
#define SERVER_HPP

#include <unistd.h>
#include <sys/select.h>
#include "../socket/SimpleSocket.hpp"
#include <vector>
#include "../parsing/HttpRequest/ParsingRequest.hpp"

class Server
{
	private:
		SimpleSocket *	socket;
		std::vector<int> vClient_socket;
		int				server_socket;
		fd_set			read_sockets;
		fd_set			current_sockets;
		fd_set			write_sockets;
		std::string		request;
	public:
		Server(int domain, int service, int protocol, int port,
				u_long interface, int backlog);
		
		void	creatSocket(int domain, int service, int protocol, int port, u_long interface, int backlog);
		void	initialize_current_sockets(void);
		void	selecter(void);
		void	accepter(void);
		// void	handler(void);
		bool	check_header(void);
		void	readSocket(int fd);
		void	responder(int index);
		void	launch(void);
};

#endif