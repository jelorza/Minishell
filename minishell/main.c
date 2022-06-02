// The list is made. needs to be freed and cleaned. thinking about implementig a bool to check if reset the static var or not.

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*line;	
	t_in	dt;
	t_pipes	*l_parseInit;

	l_parseInit = NULL;
	line = "Enter";
	if (argc != 1 || ft_compare_str(*argv, "./minishell") != 1)
	{
		printf ("Error in arguments\n");
		return (0);
	}
	ft_get_env(&dt, envp);
	while(!ft_compare_str(line, "exit"))
	{
		line = readline("minish> ");//texto de entrada de bash
		ft_between_pipes(line);
//		if (ft_break_line(line, &dt) == 1)//rompo or pipes
//			break;
//		free(line);  
  	}
//	ft_free_1(&dt);
//	free(line);
//	system ("leaks minishell");
	return (0);
}
