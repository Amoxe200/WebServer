#include "root.hpp"

void    parse_config()
{
    std::string configFile;
    std::ifstream myfile("server.conf");
    Root root(myfile);
    // while (std::getline(myfile, configFile))
    //     root.ret_key(configFile);
    // root.print_root_vector();
    myfile.close();
}

int main(){
    parse_config();
    return (0);
}