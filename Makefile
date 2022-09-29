NAME = webserv

SRCS = ./srcs/server/Server.cpp \
	   ./srcs/socket/SimpleSocket.cpp \
		./srcs/main.cpp

INCLUDES = ./srcs/server/Server.hpp \
		   ./srcs/socket/SimpleSocket.hpp

FLAGS = -Wall -Wextra -Werror -std=c++98

CC = c++

all: $(NAME)

$(NAME): $(SRCS) $(INCLUDES)
	@$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean:
	@rm -rf $(NAME)

re: fclean all
