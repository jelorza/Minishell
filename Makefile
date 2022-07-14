NAME = minishell

SRC = main.c\
	  aux_utils_0.c\
	  builtin_utils_0.c\
	  env_utils_0.c\
	  exe_utils_0.c\
	  free_utils_0.c\
	  here_doc.c\
	  linked_list.c\
	  list_utils_0.c\
	  parse_line.c\
	  red_utils_0.c\

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

