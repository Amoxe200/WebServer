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
	int server_num = 0;
	/*Check How many servers are in the config file and store there indexes*/
	for (unsigned long i = 0; i < vect.size(); i++)
	{
		for (unsigned long j = 0; j < vect[i].size(); j++)
		{
			if (vect[i][j] == "server")
			{
				server_index_vector.push_back(i);
				server_num++;
			}
		}
	}

	/*Handle Errors*/
	verify(vect, server_num);
	/*Fill the server block*/
	for (size_t i = 0; i < servers.size(); i++)
	{
		std::cout<<"Server["<<i<<"]"<<"Host = "<<servers[i].get_host()<<std::endl;
		std::cout<<"Server["<<i<<"]"<<"Port = "<<servers[i].get_port()<<std::endl;
		std::cout<<"Server["<<i<<"]"<<"server Name = "<<servers[i].get_serverName()<<std::endl;
		std::cout<<"Server["<<i<<"]"<<"Body Size = "<<servers[i].get_body_size()<<std::endl;
	}
}

std::vector<Server> Root::verify(std::vector <std::vector<std::string> > vect, int server_num)
{
  std::stack<char> stack = std::stack<char>();
  int index;
  bool in_server = false;
  bool in_location = false;
  bool server_bracket = false;
  std::vector<Server> server_vect;
	Server server_obj[server_num];


  for (size_t i = 0; i < vect.size(); i++)
    for (size_t j = 0; j < vect[i].size(); j++)
      {
		index = 0;
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
		/*Fill The data*/
			if (!j && vect[i][j] == "host:" && (in_server && !in_location))
				server_obj[index].set_host(vect, i, j);
			else if (!j && vect[i][j] == "listen:" && (in_server && !in_location))
				server_obj[index].set_port(vect, i, j);
			else if (!j && vect[i][j] == "server_name:" && (in_server && !in_location))
				server_obj[index].set_serverName(vect, i, j);
			else if (!j && vect[i][j] == "bodySize:" && (in_server && !in_location))
				server_obj[index].set_bodySize(vect, i, j);
        if (vect[i][j] == "}")
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
			if (!in_server && !in_location)
			{
				servers.push_back(server_obj[index]);
				if (index < server_num)
					index++;
			}
          }
        }

      }

  if (!stack.empty())
  {
    std::cout << "error" << std::endl;
    exit(0);
  }

  return server_vect;
}

/**********************************************************/
/*******************    GETTERS    ************************/
/**********************************************************/
/**********************************************************/

/*Remove the get vector later*/
std::vector<std::vector<std::string> > Root::get_root_vector()
{
	return vect;
}

/**********************************************************/
/*******************    Functions    ************************/
/**********************************************************/

void Root::fill_server()
{

}

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
