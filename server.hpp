#ifndef SERVER_HPP
#define SERVER_HPP
#include<iostream>
#include <stdio.h>
#include<stdlib.h>
#include <string>
#include <vector>
#include "location.hpp"

class Server{

    private:
    std::string host;
    std::string port;
    std::string serverName;
    std::string bodySize;


    /*Location Vector*/
    std::vector<Location> location;

    public:
    Server();
    ~Server();
    /**********Getters************/
    std::string get_host();
    std::string get_port();
    std::string get_serverName();
    std::string get_body_size();


    /****** SETTERS *******/
    void set_host(std::vector<std::vector<std::string> > vect, int i, int j);   
    void set_port(std::vector<std::vector<std::string> > vect, int i, int j);
    void set_serverName(std::vector<std::vector<std::string> > vect, int i, int j);
    void set_bodySize(std::vector<std::vector<std::string> > vect, int i, int j);
};


#endif