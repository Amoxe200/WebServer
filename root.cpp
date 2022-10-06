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
	if (line.compare("server:") != 0)
		fill_root(line);
	else
	{
		// map_printer();
		exit(1);
	}
    
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
	return (no_space);
}

void Root::map_printer()
{
	std::map<std::string, std::vector<std::string> >::iterator it = elements.begin();

	while (it != elements.end())
	{
		std::cout<<"[Key = "<<it->first<<"]";
		std::vector<std::string> inside_vec = it->second;
		for (unsigned i = 0; i < inside_vec.size(); i++)
			std::cout<<" [Value = "<<inside_vec[i]<<"]"<<std::endl;
		it++;
	}

}

std::map<std::string, std::string> Root::splitter(std::string line, char del)
{
	std::string key;
	std::string str_val;
	std::vector<std::string> value;
    std::map<std::string, std::string> lines;
	int startIndex = 0;
    int i = 0;
	int lent = 0;
	int start_val = 0;
 	int len_key = 0;
	int len_val = 0;

	while (line[lent])
		lent++;
	while (line[i] != del && i < lent)
		i++;
	len_key = i;
	if(line[i] == del)
		i++;
	start_val = i;
	while (line[i])
		i++;
	len_val = i;
	key = line.substr(startIndex, len_key);
	key = space_remover(key);
	str_val = line.substr(start_val, len_val);
	lines.insert(std::pair<std::string, std::string> (key, str_val));

	// value.push_back(str_val);
	// elements.insert (std::pair< std::string, std::vector<std::string> > (key, value));
	return(lines);
}

void Root::fill_root(std::string line)
{
	std::vector<std::string> value;
	std::map<std::string, std::string> key_map;


	key_map = splitter(line, ':');

	std::map<std::string, std::string> :: iterator it  = key_map.begin();
	while (it != key_map.end())
	{
	
	}

}




