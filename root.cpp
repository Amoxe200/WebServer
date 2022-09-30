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
	splitter(line);
    
	return (line);
}

std::string	Root::space_remover(std::string word)
{
	int i = 0;
	int index = 0;
	int lenght = 0;
	// char *new_word = const_cast<char *> (word.c_str());
	std::string no_space;

	while (word[lenght])
		lenght++;

	while ((word[i] == ' ' || word[i] == '\t') && i < lenght)
		i++;
	while ((word[i] != ' ' || word[i] != '\t') && i < lenght)
	{
		no_space.push_back(word[i]);
		if ((word[i] == ' ' || word[i] == '\t') && i < lenght)
			i++;
		i++;
		index++;
	}
	no_space.push_back('\0');
	// std::cout << "====["<< index<< no_space<< "]"<<std::endl;
	return (no_space);
}

void Root::splitter(std::string line)
{
	std::string key;
	std::string value;
    int startIndex = 0;
    int i = 0;
	int lent = 0;
    int lastIndex = 0;
	// int len_key = 0;
	// int len_val = 0;

    char *toSplit = const_cast<char *> (line.c_str());
    
	while (toSplit[lent])
		lent++;

    while (toSplit[i] != ':' && i < lent)
        i++;
    lastIndex = i; 
	// len_val = i;

	key = std::string(toSplit).substr(startIndex, lastIndex);
	key = space_remover(key);
	std::cout<< key << std::endl;
}