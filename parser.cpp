#include "root.hpp"

void    parse_config()
{
    std::string configFile;
    Root default_server;

    std::ifstream Myfile("server.conf");
    while (std::getline(Myfile, configFile))
        default_server.ret_key(configFile);
    Myfile.close();
}

int main(){
    parse_config();
    return (0);
}