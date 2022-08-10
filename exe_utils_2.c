/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*       jelorza- <jelorza-@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:11:33 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/08/10 08:19:57 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exe_cmd_builtin_st_aux(t_in *dt, int n)
{
	int	fd[2];
	int	pid;

	ft_pipe (fd);
	pid = ft_fork ();
	if (pid == 0)
	{
		ft_close (fd[0]);
		if (dt->fdint > 0)
			ft_close (dt->fdint);
		if (dt->fdout > 0)
		{
			ft_dup2 (dt->fdout, STDOUT_FILENO);
			ft_close (dt->fdout);
		}
		else
			ft_dup2 (fd[1], STDOUT_FILENO);
		ft_close (fd[1]);
		if (ft_builtin(dt, n) == -1)
			return (-1);
		exit(0);
	}
	else
		ft_exe_cmd_builtin_st_aux_aux(dt, fd[0], fd[1], pid);
	return (0);
}

void	ft_exe_cmd_builtin_st_aux_aux(t_in *dt, int fd0, int fd1, int pid)
{
	ft_close (fd1);
	ft_wait(pid);
	dt->fdaux = dup (fd0);
	ft_close (fd0);
}

int	ft_exe_cmd_exe_st(t_in *dt)
{
	int	fd[2];
	int	pid;

	ft_pipe (fd);
	pid = ft_fork ();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		ft_close (fd[0]);
		dt->fdaux = 0;
		ft_dup2 (dt->fdaux, STDIN_FILENO);
		ft_exe_cmd_exe_st_aux(dt, fd[1]);
		ft_close (fd[1]);
		execve (dt->rootcmd, dt->cmdf, dt->env);
		exit(0);
	}
	else
	{
		ft_close (fd[1]);
		ft_wait(pid);
		dt->fdaux = dup (fd[0]);
		ft_close (fd[0]);
	}
	return (0);
}

void	ft_exe_cmd_exe_st_aux(t_in *dt, int fd1)
{
	if (dt->fdint > 0)
	{
		ft_dup2 (dt->fdint, STDIN_FILENO);
		ft_close (dt->fdint);
	}
	if (dt->fdout > 0)
	{
		ft_dup2 (dt->fdout, STDOUT_FILENO);
		ft_close (dt->fdout);
	}
	else
		ft_dup2 (fd1, STDOUT_FILENO);
}

int	ft_exe_cmd_exe_int(t_in *dt)
{
	int	fd[2];
	int	pid;

	ft_pipe(fd);
	pid = ft_fork ();
	if (pid == 0)
	{
		ft_close (fd[0]);
		ft_exe_cmd_exe_int_aux(dt, fd[1]);
		ft_close (fd[1]);
		execve (dt->rootcmd, dt->cmdf, dt->env);
		exit(0);
	}
	else
	{
		ft_close (fd[1]);
		if (dt->fdaux > 0)
			ft_close (dt->fdaux);
		ft_wait(pid);
		if (fd[0] > 0)
			dt->fdaux = dup (fd[0]);
		ft_close (fd[0]);
	}
	return (0);
}
