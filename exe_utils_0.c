/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/11 15:33:53 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec(t_in *dt)
{
	ft_clean(dt);
	if (dt->l_parse_cmd)
	{
		while (dt->l_parse_cmd)
		{
			dt->cmdf = ft_split_echo(dt->l_parse_cmd->data, ' ');
			dt->ncmd = ft_strdup(dt->cmdf[0]);
			if (ft_exec_aux(dt) == -1)
				return (-1);
			ft_free(dt, 0);
			dt->l_parse_cmd = dt->l_parse_cmd->next;
		}
	}
	else if (dt->l_parse_cmd == NULL && dt->l_parse_redir)
		ft_redir_null(dt);
	return (0);
}

int	ft_exec_aux(t_in *dt)
{
	int	i;

	i = ft_ch_cmde(dt);
	if ((ft_ch_buil(dt->ncmd, dt->l_parse_cmd) >= 0
			&& ft_ch_buil(dt->ncmd, dt->l_parse_cmd) <= 6) || i == 0)
	{
		if (dt->l_parse_redir && dt->l_parse_redir->id < dt->l_parse_cmd->id)
			ft_redir_null(dt);
		if (ft_execve (dt, dt->l_parse_cmd->id) == -1)
			return (-1);
	}
	else
	{
		g_status = 127;
		if (i == -2)
			printf ("bash: %s: No such file or directory\n", dt->rootcmd);
		else
			printf ("bash: %s: command not found\n", dt->ncmd);
	}
	return (0);
}

void	ft_clean(t_in *dt)
{
	dt->fdaux = -2;
	dt->an = 0;
	dt->rootcmd = NULL;
	dt->cmdf = NULL;
	dt->cmdf_echo = NULL;
	dt->cr = NULL;
	dt->hd_i = dt->l_parse_init;
	dt->hd_r = dt->l_parse_redir;
	dt->hd_c = dt->l_parse_cmd;
	dt->nc = ft_listlen(dt->l_parse_cmd);
	dt->l_parse_cmd = dt->hd_c;
}

int	ft_execve(t_in *dt, int n)
{
	int		i;

	if (ft_ch_redir (dt, n) == -1)
		return (-1);
	i = ft_exe_redir(dt, n);
	if (i == -1)
		return (-1);
	else if (i == -2)
		return (-2);
	if (ft_exe_cmd(dt, n) == -1)
		return (-1);
	return (0);
}

int	ft_exe_cmd(t_in *dt, int n)
{
	if ((ft_ch_buil(dt->ncmd, dt->l_parse_cmd) >= 0
			&& ft_ch_buil(dt->ncmd, dt->l_parse_cmd) <= 6))
	{
		if (ft_exe_cmd_builtin(dt, n) == -1)
			return (-1);
	}
	else
	{
		rl_catch_signals = 1;
		if (ft_exe_cmd_exe(dt, n) == -1)
			return (-1);
		rl_catch_signals = 0;
	}
	return (0);
}
