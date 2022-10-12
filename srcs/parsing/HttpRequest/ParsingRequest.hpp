#ifndef PARSINGREQUEST_HPP
#define PARSINGREQUEST_HPP

#include <string>

// enum HTTPMethods
// {
//     GET = 1,
//     POST = 2,
//     DELETE = 3
// };


class ParsingRequest
{
    private:
        char            *method;
        char            *URI;
    public:
        ParsingRequest(char *request);
        ~ParsingRequest();

        void    end_header_fields(char **request);
        void    request_line(char *request_line);
        void    header_fields(char *header_fields);
};

#endif