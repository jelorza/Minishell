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
	  expand_envs1.c\
	  expand_envs2.c\
	  div_in_list1.c\
	  div_in_list2.c\
	  div_in_list3.c\
	  pipes_list.c\

OBJ = $(SRC:.c=.o)

CC = gcc -g3

READLINE_DIR = ${HOME}/.brew/opt/readline


FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
F_READLINE = -I$(READLINE_DIR)/include
COMPILE = -lreadline -L$(READLINE_DIR)/lib

.c.o: $(SRC)
	$(CC) $(FLAGS) $(F_READLINE) -c -o $@ $<


$(NAME):$(OBJ)
		$(CC) $(FLAGS) -o $(NAME) $(COMPILE) $(OBJ) $(LIBFT)

all: $(NAME)

clean:
		/bin/rm -f $(OBJ)

fclean: clean
		/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
