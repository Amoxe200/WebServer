#ifndef ROOT_HPP
#define ROOT_HPP
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include "server.hpp"

class Root {

private:
std::vector<Server> servers;


protected:
std::string index;
std::string i_val;
std::string body_size;
std::string size;
std::string allowed_mtd;
std::string type_mtd;
std::string auto_index;
std::string status;


public:
    Root();
    ~Root();
    std::map<std::string, std::string> elements;.
};


#endif