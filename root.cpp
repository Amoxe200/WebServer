#include "root.hpp"

/**********************************************************/
/*******************    METHODS    ************************/
/**********************************************************/

Root::Root(std::ifstream &myfile)
{
    std::cout<<"Parameterized constructor called"<<std::endl;
	std::string line;
	while (std::getline(myfile, line))
	{
		if (line.empty())
			continue;
		vect.push_back(custom_split(line, ' '));
	}
	/***** Remove Later the printer ****/
	// print_root_vector();
	/**** Parsing ****/
	parser();
}

Root::~Root()
{
    std::cout<<"Destructor called"<<std::endl;
}


/****** Parser Function where all the parsing happening ********/

void Root::parser()
{
	std::vector<int> server_index_vector; // server vector index
	int servers = 0;
	/*Check How many servers are in the config file and store there indexes*/
	for (unsigned long i = 0; i < vect.size(); i++)
	{
		for (unsigned long j = 0; j < vect[i].size(); j++)
		{
			if (vect[i][j] == "server")
			{
				server_index_vector.push_back(i);
				servers++;
			}
		}
	}

	/*Get the data from the vector*/
	verify(vect);

}

bool Root::verify(std::vector <std::vector<std::string> > vect)
{
  std::stack<char> stack = std::stack<char>();
  bool in_server = false;
  bool in_location = false;
  bool server_bracket = false;
  for (size_t i = 0; i < vect.size(); i++)
    for (size_t j = 0; j < vect[i].size(); j++)
      {
        if (vect[i][j] == "server")
        {
			
          if (in_server)
          {
            std::cout << "server error "<< std::endl;
            exit(0);
          }
          else
            in_server = true;
        }

        if (vect[i][j] == "location")
        {
          if (!in_server || in_location)
          {
            std::cout << "location error" << std::endl;
            exit(0);
          }
          else
            in_location= true;
        }

        if (vect[i][j] == "{")
        {
          if (in_server)
          {
			if (!server_bracket)
				server_bracket = true;
			else if (!in_location)
			{
				std::cout<<"error bracket location"<<std::endl;
				exit(1);
			}
          }
		  else
		  {
			std::cout << "block name error" << std::endl;
            exit(0);
		  }
          stack.push('{');
        }
        else if (vect[i][j] == "}")
        {
          if (stack.empty())
          {
            std::cout << "error" << std::endl;
            exit(0);
          }
          else
          {
            if (in_location)
              in_location = false;
            else if (in_server)
			{
              in_server = false;
				server_bracket = false;
			}
            stack.pop();
          }
        }
      }
  if (!stack.empty())
  {
    std::cout << "error" << std::endl;
    exit(0);
  }

  return true;
}




// void Root::parse_vector(std::vector<int> server_index_vector, int servers)
// {
// 	std::stack<char> stack = std::stack<char>();
// 	(void)server_index_vector;
// 	(void)servers;
// 	/*Check If the first element of the vector is server*/
// 	if (vect[0][0] == "server")
// 	{
// 		for (unsigned long i = 0; i < vect.size(); i++)
// 		{
// 			for (unsigned long j = 0; j < vect[i].size(); j++)
// 			{
// 				if (vect[i][j] == "{")
// 				{
// 					stack.push('{');
// 				}
// 				else if (vect[i][j] == "}")
// 				{
// 					if (stack.empty())
// 					{
// 						std::cout<<"Bracket Error"<<std::endl;
// 						exit(1);
// 					}
// 					else
// 					{
// 						stack.pop();
// 					}
// 				}

// 			}
// 		}
// 		if (!stack.empty())
// 		{
// 			std::cout<<"Error Brackets"<<std::endl;
// 			exit(1);
// 		}
// 	}
// 	else 
// 	{
// 		std::cout<<"Config file must start with server"<<std::endl;
// 		exit(1);
// 	}

// }

/**********************************************************/
/*******************    GETTERS    ************************/
/**********************************************************/

/*Remove the get vector later*/
std::vector<std::vector<std::string> > Root::get_root_vector()
{
	return vect;
}

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

	while ((word[i] == ' '  || word[i] == '\t') && i < lenght)
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

std::vector<std::string> Root::custom_split(std::string line, char del)
{
	int lenght = 0;
	int index = 0;
	int start = 0;
	int last = 0;
	std::string str = "";
	std::vector <std::string> lines;

	while (line[lenght])
		lenght++;
	while (index < lenght)
	{
		while (line[index] != del && line[index])
			index++;
		last = index;
		str = line.substr(start, (last - start));
		while (line[index] == del && line[index])
			index++;
		start = index;
		str = space_remover(str);
		lines.push_back(str);
		index++;
	}
	return (lines);
}


void Root::print_root_vector()
{
	for (unsigned long i = 0; i < vect.size(); i++)
	{
		std::cout<<"Vector Number [" << i << "]" << std::endl;
		for (unsigned long j = 0; j < vect[i].size(); j++)
		{
            std::cout<<"Vector element " << j << " : ";
			std::cout<< vect[i][j] << " ";
		}
		std::cout<<std::endl;
	}
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