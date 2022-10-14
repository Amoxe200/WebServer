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
std::string index;
std::vector<std::pair<std::string, std::string> > errorPage;
int bodySize;
std::vector<std::string> method;
std::string autoIndex;
std::string cgiPath;
std::vector<std::string> config_vector;
std::vector<std::string> cgiExt;
std::vector<Server> servers;

public:
	Root();
	~Root();
	/******* Getters *********/
	std::string get_index();
	std::vector<std::pair<std::string, std::string> > get_errorPage();
	int get_bodySize();
	std::vector<std::string> get_method();
	std::string get_autoIndex();
	std::string get_cgiPath();
	std::vector<std::string> get_cgiExt();

	/******* SETTERS ********/
	void set_index();
	void set_errorPage();
	void set_bodySize();
	void set_method();
	void set_autoIndex();
	void set_cgiPath();
	void set_cgiExt();

	std::map<std::string, std::vector<std::string> > elements;
	std::string ret_key(std::string line);
	std::vector<std::string> custom_split(std::string line, char del);
	std::map<std::string, std::string> splitter(std::string line, char del);
	void vec_print(std::vector<std::string> vector);
	// void fill_root(std::string line);
	void map_printer();
	std::string space_remover(std::string word);
};

#endif