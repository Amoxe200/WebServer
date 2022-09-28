#include "root.hpp"

Root::Root(){

    std::cout<<"Default constructor called"<<std::endl;
}

Root::~Root()
{
    std::cout<<"Destructor called"<<std::endl;
}

std::string Root::ret_key(std::string line)
{
    
    return (line);
}