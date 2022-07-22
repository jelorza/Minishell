NAME = minishell

SRC = main.c\
	  aux_utils_0.c\
	  builtin_utils_0.c\
	  env_utils_0.c\
	  exe_utils_0.c\
	  free_utils_0.c\
	  here_doc.c\
	  linked_list_newnod.c\
	  linked_list_print.c\
	  linked_list_clean.c\
	  linked_list_addnod.c\
	  list_utils_0.c\
	  parse_line.c\
	  red_utils_0.c\
	  signal_utils_0.c\

OBJ = $(SRC: .c=.o)  

READLINE_DIR = ${HOME}/.brew/opt/readline

CC = gcc -g3
FLAGS = -Wall -Werror -Wextra
F_RD1 = -I$(READLINE_DIR)/include
F_RD2 = -lreadline -L$(READLINE_DIR)/lib
SAN = -fsanitize=address

RM = rm -r -f

all: $(NAME)

.c.o: $(SRC)
	$(CC) $(FLAGS) $(F_RD1) -c -o $@ $<

$(NAME): $(OBJ)
#	$(CC) $(FLAGS) -c $(OBJ) $(SRC)
	$(CC) $(FLAGS) -o $(NAME) $(F_RD2) $(OBJ) #$(SAN)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)
	$(RM) *.dSYM

re:	fclean all

.PHONY: name, all, clean, fclean, re
