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
    std::map<std::string, std::string> elements;
    std::string ret_key(std::string line);
};


#endif