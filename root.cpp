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
	// no_space.push_back('\0');
	return (no_space);
}

void Root::map_printer()
{
	std::map<std::string, std::string>::iterator it = elements.begin();

	while (it != elements.end())
	{
		std::cout<<"Key = ["<<it->first<<"] Value = "<<it->second<<std::endl;
		it++;
	}
}

void Root::splitter(std::string line)
{
	std::string key;
	std::string value;
    int startIndex = 0;
    int i = 0;
	int lent = 0;
    int start_val = 0;
 	int len_key = 0;
	int len_val = 0;

   if (line.compare("server:") != 0)
   {
		while (line[lent])
			lent++;
		while (line[i] != ':' && i < lent)
			i++;
		len_key = i;
		if(line[i] == ':')
			i++;
		start_val = i;
		while (line[i])
			i++;
		len_val = i;
		key = line.substr(startIndex, len_key);
		key = space_remover(key);
		value = line.substr(start_val, len_val);
		elements.insert (std::pair<std::string, std::string> (key, value));
   }
   else
   {
	map_printer();
	exit(1);
   }
}