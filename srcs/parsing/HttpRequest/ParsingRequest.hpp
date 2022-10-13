#ifndef PARSINGREQUEST_HPP
#define PARSINGREQUEST_HPP

#include <string>
#include <map>
#include <iostream>

enum HTTPfields
{
   //Authorization,
    Content_Length,
    Content_Type,
    Host,
    Connection
};


class ParsingRequest
{
    protected:
        char            *method;
        char            *URI;
        std::map<int, std::string>  errors;
        std::map<int, std::string>  fields;
    public:
        ParsingRequest(char *request);
        ~ParsingRequest();

        void    end_header_fields(char **request);
        void    request_line(char *request_line);
        void    header_fields(char *header_fields);
        void    set_errors(void);
};

#endif