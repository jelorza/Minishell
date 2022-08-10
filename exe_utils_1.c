/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*       jelorza- <jelorza-@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:11:33 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/08/10 08:19:36 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exe_cmd_builtin(t_in *dt, int n)
{
	dt->l_parse_init = dt->hd_i;
	if (n == ft_listlen(dt->l_parse_init) - 1)
	{
		if (ft_exe_cmd_builtin_end(dt, n) == -1)
			return (-1);
	}
	else
	{
		if (ft_exe_cmd_builtin_st(dt, n) == -1)
			return (-1);
	}
	return (0);
}

int	ft_exe_cmd_exe(t_in *dt, int n)
{
	dt->l_parse_init = dt->hd_i;
	if (n == 0 && n != ft_listlen(dt->l_parse_init) - 1)
	{
		if (ft_compare_str_cat(dt->ncmd) == 1 && !dt->cmdf[1])
		{
			dt->an = 1;
			return (0);
		}
		else if (ft_exe_cmd_exe_st(dt) == -1)
			return (-1);
	}
	else if (n != 0 && n != (ft_listlen(dt->l_parse_init) - 1))
	{
		if (ft_compare_str_cat(dt->ncmd) == 1 && dt->an == 1)
			return (0);
		else if (ft_exe_cmd_exe_int(dt) == -1)
			return (-1);
	}
	else if (n == ft_listlen(dt->l_parse_init) - 1)
	{
		if (ft_exe_cmd_exe_end(dt) == -1)
			return (-1);
	}
	return (0);
}

int	ft_exe_cmd_builtin_st(t_in *dt, int n)
{
	if (ft_compare_str(dt->ncmd, "pwd") == 1
		|| ft_compare_str(dt->ncmd, "env") == 1
		|| ft_compare_str(dt->ncmd, "echo") == 1)
	{
		if (ft_exe_cmd_builtin_st_aux(dt, n) == -1)
			return (-1);
		return (0);
	}
	if (dt->fdout > 0)
		ft_close (dt->fdout);
	if (dt->fdint > 0)
		ft_close (dt->fdint);
	if (dt->fdaux > 0)
	{
		ft_close (dt->fdaux);
		dt->fdaux = -2;
	}
	if (ft_builtin(dt, n) == -1)
		return (-1);
	return (0);
}

int	ft_exe_cmd_builtin_end(t_in *dt, int n)
{
	if (dt->fdint > 0)
		ft_close (dt->fdint);
	else if (dt->fdaux > 0)
		ft_close (dt->fdaux);
	if (dt->fdout > 0)
	{
		if (ft_compare_str(dt->ncmd, "pwd") == 1
			|| ft_compare_str(dt->ncmd, "env") == 1
			|| ft_compare_str(dt->ncmd, "echo") == 1)
		{
			if (ft_builtin_fork (dt, n) == -1)
				return (-1);
		}
		ft_close (dt->fdout);
	}
	else
	{
		if (ft_builtin(dt, n) == -1)
			return (-1);
	}
	return (0);
}

int	ft_builtin_fork(t_in *dt, int n)
{
	int	pid;

	pid = ft_fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		ft_dup2 (dt->fdout, STDOUT_FILENO);
		ft_close (dt->fdout);
		ft_builtin(dt, n);
		exit (0);
	}
	else
	{
		ft_wait (pid);
		if (dt->fdaux > 0)
			ft_close (dt->fdaux);
	}
	return (0);
}
