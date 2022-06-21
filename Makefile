NAME = minishell

SRC = main.c\
	  arg_utils_0.c\
	  env_utils_0.c\
	  aux_utils_0.c\
	  free_utils_0.c\
	  ft_parse_line.c\
	  ft_linked_list.c

OBJ = $(SRC: .c=.o)  

CC = gcc
FLAGS = -Wall -Werror -Wextra -g #-pthread
FLAGS_TWO = -lreadline
SAN = -g3 -fsanitize=address

RM = rm -r -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -c $(OBJ) $(SRC)
	$(CC) $(FLAGS) $(FLAGS_TWO) $(OBJ) -o $(NAME) $(SAN)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)
	$(RM) *.dSYM

re:	fclean all

phony: name, all, clean, fclean, re 

