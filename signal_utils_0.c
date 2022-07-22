#include "minishell.h"

//funcion principal que distribuye las señales
void	ft_signal(void)
{
	signal(SIGINT, signal_c);
	signal(SIGQUIT, SIG_IGN);
}

//funcion del cnt-c
void	signal_c(int signum)
{
	if (rl_on_new_line() == -1)
		exit (-1);
	if (SIGINT == signum)
	{
		write(1, "\n", 1);
//		rl_replace_line("", 1);
		rl_redisplay();
		STATUS = 1;
	}
}
