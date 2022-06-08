#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*line;	
	t_in	dt;


	if (argc != 1 || ft_compare_str(*argv, "./minishell") != 1)
	{
		printf ("Error in arguments\n");
		return (0);
	}
	ft_get_env(&dt, envp);
	while(1)
	{
		line = readline("minish> ");//texto de entrada de bash
		if (!line || line[0] == 'E')//compruebo fallo del line
			break;
		if (ft_break_line(line, &dt) == 1)//rompo por pipes
			break;
		free(line);  
  	}
	ft_free_1(&dt);
	free(line);
	system ("leaks minishell");
	return (0);
}
