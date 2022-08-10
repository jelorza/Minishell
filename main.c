/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/10 08:26:18 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Hay que checar por que se queda olgado << hola | wc, y solo << o solo <

#include "minishell.h"

void	ft_struct_init(t_in *dt, char **envp)
{
	g_status = 0;
	dt->l_parse_init = NULL;
	dt->hd_i = NULL;
	dt->l_parse_redir = NULL;
	dt->hd_r = NULL;
	dt->l_parse_cmd = NULL;
	dt->hd_c = NULL;
	dt->hd = NULL;
	dt->hd_h = NULL;
	dt->env = NULL;
	dt->env_name = NULL;
	dt->env_value = NULL;
	dt->ncmd = NULL;
	dt->rootcmd = NULL;
	dt->root = NULL;
	dt->rootold = NULL;
	dt->cmdf = NULL;
	dt->cr = NULL;
	ft_get_env(dt, envp);
	rl_catch_signals = 0;
	ft_signal ();
}

void	ft_clean_all_lists(t_in *dt)
{
	if (dt->hd_i)
	{
		dt->l_parse_init = dt->hd_i;
		dt->hd_i = NULL;
	}
	ft_clean_list_pipe(&dt->l_parse_init);
	if (dt->hd_c)
	{
		dt->l_parse_cmd = dt->hd_c;
		dt->hd_c = NULL;
	}
	ft_clean_list_cmd(&dt->l_parse_cmd);
	if (dt->hd_r)
	{
		dt->l_parse_redir = dt->hd_r;
		dt->hd_r = NULL;
	}
	ft_clean_list_redir(&dt->l_parse_redir);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;	
	t_in	dt;

	line = NULL;
	if (argc != 1 || ft_compare_str(*argv, "./minishell") != 1)
	{
		printf ("Error in arguments\n");
		return (0);
	}
	ft_struct_init(&dt, envp);
	while (1)
	{
		line = readline("bash-jonpol$ ");
		add_history (line);
		if (!line)
		{
			printf ("exit\n");
			break ;
		}
		if (ft_parse_line(line, &dt) == -1)
			break ;
		ft_free_parcial (&dt, line);
	}
	ft_free_all(&dt, line);
	return (g_status);
}
