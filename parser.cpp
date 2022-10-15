#include "root.hpp"

void    parse_config()
{
    std::string configFile;
    Root root;

    std::ifstream Myfile("server.conf");
    while (std::getline(Myfile, configFile))
        root.ret_key(configFile);
    root.print_root_vector();
    Myfile.close();
}

int main(){
    parse_config();
    return (0);
}