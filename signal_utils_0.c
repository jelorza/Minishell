#include "minishell.h"

//funcion principal que distribuye las señales
void	ft_signal(void)
{
	signal(SIGINT, signal_c);
	signal(SIGQUIT, signal_b);
}

//funcion del cnt-c
void	signal_c(int signum)
{
	if (SIGINT == signum && rl_catch_signals == 0 && STATUS != -23)//señal en el promt inicial
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		STATUS = 1;
	}
	else if (SIGINT == signum && rl_catch_signals == 1 && STATUS != -23)//señal en el hijo
	{
		write(1, "\n", 1);
		STATUS = 130;
	}
	else if (SIGINT == signum && STATUS == -23)//señal en el HD
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		STATUS = 1;
	}
}

//funcion del cnt-\ (que realmente es el cnt-4)
void	signal_b(int signum)
{
	if (SIGQUIT == signum && rl_catch_signals == 1)
	{
		STATUS = 131;
		write(1, "Quit : 3\n", 9);
	}
}
