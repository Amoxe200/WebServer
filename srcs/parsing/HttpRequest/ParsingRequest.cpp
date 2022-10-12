#include "ParsingRequest.hpp"

ParsingRequest::ParsingRequest(char *request)
{
    end_header_fields(&request);
    request_line(strtok(request, "\n"));
    header_fields(strtok(NULL, "\n"));
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
        perror("Wrong METHOD\n");
        exit(EXIT_FAILURE);
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
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
    this->errors.insert(std::pair<int, std::string>(501, "Not Implemented"));
}
// bool ParsingRequest::operator==(const ParsingRequest & rhs) const
// {
//     i
// }