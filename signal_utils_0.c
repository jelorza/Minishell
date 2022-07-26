/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/26 12:33:26 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal(void)
{
	signal(SIGINT, signal_c);
	signal(SIGQUIT, signal_b);
}

void	signal_c(int signum)
{
	if (SIGINT == signum && rl_catch_signals == 0 && g_status != -23)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
	else if (SIGINT == signum && rl_catch_signals == 1 && g_status != -23)
	{
		write(1, "\n", 1);
		g_status = 130;
	}
	else if (SIGINT == signum && g_status == -23)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
}

void	signal_b(int signum)
{
	if (SIGQUIT == signum && rl_catch_signals == 1)
	{
		g_status = 131;
		write(1, "Quit : 3\n", 9);
	}
}
