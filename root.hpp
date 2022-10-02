#ifndef ROOT_HPP
#define ROOT_HPP
#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>
#include <vector>
#include <fstream>
#include <cstring>
#include "server.hpp"

class Root {

private:
std::vector<Server> servers;

public:
	Root();
	~Root();
	std::map<std::string, std::string> elements;
	std::string ret_key(std::string line);
	void splitter(std::string line);
	std::string space_remover(std::string word);
	void map_printer();
};

#endif