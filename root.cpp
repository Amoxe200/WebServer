#include "root.hpp"

/**********************************************************/
/*******************    METHODS    ************************/
/**********************************************************/


Root::Root(){

    std::cout<<"Default constructor called"<<std::endl;
}

Root::~Root()
{
    std::cout<<"Destructor called"<<std::endl;
}

std::string Root::ret_key(std::string line)
{
	// int left_bracket = 0;
	// int right_bracket = 0;
	std::vector<std::string> lines;
	int index = 0;
	while((line[index] == ' ' || line[index] == '\t' || line[index] == '\n') && line[index])
		index++;
	lines = custom_split(line, ' ');
	vec_print(lines);
	// splitter(line, ':');
	// // else
	// {
	// 	map_printer();
	// 	exit(1);
	// }
	return (line);
}

/**********************************************************/
/*******************    GETTERS    ************************/
/**********************************************************/

std::string Root::get_index()
{
	return index;
}

std::vector<std::pair<std::string, std::string> > Root::get_errorPage()
{
	return errorPage;
}

int Root::get_bodySize()
{
	return bodySize;
}

std::vector<std::string> Root::get_method()
{
	return method;
}

std::string Root::get_autoIndex()
{
	return autoIndex;
}

std::string Root::get_cgiPath()
{
	return cgiPath;
}

std::vector<std::string> Root::get_cgiExt()
{
	return cgiExt;
}

/**********************************************************/
/*******************    SETTERS    ************************/
/**********************************************************/






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

void Root::vec_print(std::vector<std::string> vector)
{
	std::vector<std::string>::iterator i;
	for (i = vector.begin(); i < vector.end(); i++)
			std::cout<<"element = " << *i << std::endl;
}

std::vector<std::string> Root::custom_split(std::string line, char delim)
{
	int lenght = 0;
	int i = 0;
	int startIndex = 0;
	int endIndex = 0;
	std::string new_line = "";
	std::vector<std::string> splited;

	while (line[lenght])
		lenght++;

	while (i < lenght)
	{
		if (line[i] == delim)
		{
			endIndex = i;
			new_line = line.substr(startIndex, endIndex);
			splited.push_back(new_line);
			startIndex = endIndex + 1;
		}
		i++;
	}

	return(splited);
}

// std::map<std::string, std::string> Root::splitter(std::string line, char del)
// {
// 	std::string key;
// 	std::string str_val;
// 	std::vector<std::string> value;
//     std::map<std::string, std::string> lines;
// 	int startIndex = 0;
//     int i = 0;
// 	int lent = 0;
// 	int start_val = 0;
//  	int len_key = 0;
// 	int len_val = 0;

// 	while (line[lent])
// 		lent++;
// 	while (line[i] != del && i < lent)
// 		i++;
	
// 	len_key = i;
// 	if(line[i] == del)
// 		i++;
// 	start_val = i;
// 	while (line[i])
// 		i++;
	
// 	len_val = i;
// 	key = line.substr(startIndex, len_key);
// 	key = space_remover(key);
// 	str_val = line.substr(start_val, len_val);
// 	lines.insert(std::pair<std::string, std::string> (key, str_val));
// 	value.push_back(str_val);
// 	elements.insert (std::pair< std::string, std::vector<std::string> > (key, value));
// 	return(lines);
// }

// void Root::fill_root(std::string line)
// {
// 	std::vector<std::string> value;
// 	std::map<std::string, std::string> key_map;

// 	key_map = splitter(line, ':');

// 	std::map<std::string, std::string> :: iterator it  = key_map.begin();

// 	while (it != key_map.end())
// 	{
// 		// std::cout<<"[key = " << it->first << " ] "<< " [value = "<<it->second << " ]"<< std::endl;

// 		std::cout<<"Value = "<< it->second << std::endl;
// 		it++;
// 	}
// }