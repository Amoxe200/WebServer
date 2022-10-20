#ifndef ROOT_HPP
#define ROOT_HPP
#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>
#include <vector>
#include <fstream>
#include <cstring>
#include <stack>
#include "server.hpp"

class Root { 

private:
std::vector<Server> servers;
std::vector<std::vector<std::string> > vect;

public:
	Root(std::ifstream &myfile);
	~Root();
	/*(Parsing Functions)*/
	void parser();
	std::vector<Server> verify(std::vector <std::vector<std::string> > vect, int server_num);
	void fill_server();
	std::vector<std::vector<std::string> > get_root_vector();
	std::string ret_key(std::string line);
	std::vector<std::string> custom_split(std::string line, char del);
	void vec_print(std::vector<std::string> vector);	
	std::string space_remover(std::string word);
	void print_root_vector();
};

#endif