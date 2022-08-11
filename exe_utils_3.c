/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*       jelorza- <jelorza-@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:11:33 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/08/11 16:12:56 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exe_cmd_exe_int_aux(t_in *dt, int fd1)
{
	if (dt->fdint > 0)
	{
		ft_dup2 (dt->fdint, STDIN_FILENO);
		ft_close (dt->fdint);
	}
	else if (dt->fdaux > 0)
	{
		ft_dup2 (dt->fdaux, STDIN_FILENO);
		ft_close (dt->fdaux);
	}
	if (dt->fdout > 0)
	{
		ft_dup2 (dt->fdout, STDOUT_FILENO);
		ft_close (dt->fdout);
	}
	else
		ft_dup2 (fd1, STDOUT_FILENO);
}

int	ft_exe_cmd_exe_end(t_in *dt)
{
	int		pid;
	char	*linenull;

	pid = ft_fork ();
	if (pid == 0)
	{
		ft_exe_cmd_exe_end_aux(dt);
		execve (dt->rootcmd, dt->cmdf, dt->env);
		exit(0);
	}
	else
		ft_wait (pid);
	if (dt->fdaux > 0)
		ft_close (dt->fdaux);
	if (dt->an == 1)
	{
		linenull = NULL;
		linenull = readline("");
		free (linenull);
	}
	return (0);
}

void	ft_exe_cmd_exe_end_aux(t_in *dt)
{
	if (dt->fdint > 0)
	{
		ft_dup2 (dt->fdint, STDIN_FILENO);
		ft_close (dt->fdint);
	}
	else if (dt->fdaux > 0)
	{
		ft_dup2 (dt->fdaux, STDIN_FILENO);
		ft_close (dt->fdaux);
	}
	if (dt->fdout > 0)
	{
		ft_dup2 (dt->fdout, STDOUT_FILENO);
		ft_close (dt->fdout);
	}
}

int	ft_ch_buil(char *name, t_list *list)
{
	int	i;

	i = -1;
	if (ft_compare_str (name, "cd") == 1)
		i= 0;
	if (ft_compare_str (name, "echo") == 1)
		i = 1;
	if (ft_compare_str (name, "env") == 1)
		i = 2;
	if (ft_compare_str (name, "exit") == 1)
		i = 3;
	if (ft_compare_str (name, "export") == 1)
		i = 4;
	if (ft_compare_str (name, "pwd") == 1)
		i = 5;
	if (ft_compare_str (name, "unset") == 1)
		i = 6;
	if (i != -1)
	{
		list->type = 1;
		return (i);
	}
	return (i);
}
	
int	ft_ch_cmde(t_in *dt)
{
	int	i;

	if (dt->ncmd && dt->ncmd[0] == '/')
	{
		dt->rootcmd = ft_strdup(dt->ncmd);
		free (dt->ncmd);
		dt->ncmd = NULL;
		dt->ncmd = ft_get_name_bis(dt->rootcmd);
		if (!dt->ncmd)
			return (-2);
		if (access(dt->rootcmd, F_OK) == 0)
			return (0);
		return (-2);
	}
	else
		i = ft_ch_cmde_aux(dt);
	return (i);
}
