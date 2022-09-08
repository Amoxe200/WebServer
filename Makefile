NAME = webserv

SRCS = ./srcs/

INCLUDES = ./includes/

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