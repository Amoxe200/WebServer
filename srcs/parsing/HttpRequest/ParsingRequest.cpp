#include "ParsingRequest.hpp"

ParsingRequest::ParsingRequest(char *request)
{
    char *request_ln;;
    char *header_fiel;

    end_header_fields(&request);
    request_ln = strtok(request, "\n");
    header_fiel = strtok(NULL, "\n");
    request_line(request_ln);
    header_fields(header_fiel);
}

void    ParsingRequest::end_header_fields(char **request)
{
    for(int i = 0; i < strlen(*request) - 1; i++)
    {
        if ((*request)[i] == '\n' && (*request)[i + 1] == '\n')
        {
            (*request)[i + 1] = '$';
        }
    }
}

void    ParsingRequest::request_line(char *request_line)
{
    int     check = 0;
    char *token;
    char  *methods[] = {"GET", "POST", "DELETE"};
   
    token = strtok(request_line, " ");
    for (size_t i = 0; i < 3; i++)
    {
        if (token == methods[i])
        {
            this->method = methods[i];
            check = 1;
        }
    }
    if (check == 0)
    {
        std::cout << "RESPONSE 405" << std::endl;
    }
    token = strtok(NULL, " ");
    this->URI = token;

    return ;
}

void    ParsingRequest::header_fields(char *header_fields)
{
    

    return;
}

void    ParsingRequest::set_errors(void)
{
    this->errors.insert(std::pair<int, std::string>(200, "OK"));
    this->errors.insert(std::pair<int, std::string>(201, "Created"));
    this->errors.insert(std::pair<int, std::string>(204, "No Content"));
    this->errors.insert(std::pair<int, std::string>(301, "Moved Permanently"));
    this->errors.insert(std::pair<int, std::string>(400, "Bad Request"));
    this->errors.insert(std::pair<int, std::string>(403, "Forbidden"));
    this->errors.insert(std::pair<int, std::string>(404, "Not Found"));
    this->errors.insert(std::pair<int, std::string>(405, "Method Not Allowed"));
    this->errors.insert(std::pair<int, std::string>(409, "Conflict"));
    this->errors.insert(std::pair<int, std::string>(413, "Payload Too Large"));
    this->errors.insert(std::pair<int, std::string>(414, "URI Too Long"));
    this->errors.insert(std::pair<int, std::string>(500, "Internal Server Error"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));

    return;
}