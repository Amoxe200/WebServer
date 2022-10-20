#include "server.hpp"

Server::Server(){}

Server::~Server(){}

/**********************************************************/
/*******************    GETTERS    ************************/
/**********************************************************/

std::string Server::get_host()
{
	return host;
}

std::string Server::get_body_size()
{
	return bodySize;
}

std::string Server::get_port()
{
	return port;
}

std::string Server::get_serverName()
{
    return serverName;
}

/**********************************************************/
/*******************    SETTERS    ************************/
/**********************************************************/

void Server::set_host(std::vector<std::vector<std::string> > vect, int i, int j)
{  
    if (vect[i].size() <= 2)
        this->host = vect[i][j + 1];
    else
    {
        std::cout<<"Multiple Element in host"<<std::endl;
        exit(1);
    }
}

void Server::set_port(std::vector<std::vector<std::string> > vect, int i, int j)
{
      this->port = vect[i][j + 1];
}

void Server::set_serverName(std::vector<std::vector<std::string> > vect, int i, int j)
{
    this->serverName = vect[i][j + 1];

}

void Server::set_bodySize(std::vector<std::vector<std::string> > vect, int i, int j)
{
    this->bodySize = vect[i][j + 1];
}