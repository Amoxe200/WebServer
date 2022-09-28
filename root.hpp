#ifndef ROOT_HPP
#define ROOT_HPP
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <fstream>
#include "server.hpp"

class Root {

private:
std::vector<Server> servers;

public:
    Root();
    ~Root();
	std::string ret_key(std::string line);
	void	space_remove(std::string line);

    std::map<std::string, std::string> elements;
    
};


#endif