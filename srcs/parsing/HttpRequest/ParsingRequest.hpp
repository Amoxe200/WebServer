#ifndef PARSINGREQUEST_HPP
#define PARSINGREQUEST_HPP

#include <string>
#include <map>
#include <iostream>

// enum HTTPMethods
// {
//     GET = 1,
//     POST = 2,
//     DELETE = 3
// };


class ParsingRequest
{
    protected:
        char            *method;
        char            *URI;
        std::map<int, std::string>  errors;
    public:
        ParsingRequest(char *request);
        ~ParsingRequest();

        void    end_header_fields(char **request);
        void    request_line(char *request_line);
        void    header_fields(char *header_fields);
        void    set_errors(void);
};

#endif