/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/10 07:20:13 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec(t_in *dt)
{
	int	i;

	ft_clean(dt);
	if (dt->l_parse_cmd)
	{
		while (dt->l_parse_cmd)
		{
			dt->cmdf = ft_split_echo(dt->l_parse_cmd->data, ' ');
			dt->ncmd = ft_strdup(dt->cmdf[0]);
			i = ft_ch_cmde(dt);
			if ((ft_ch_buil(dt->ncmd, dt->l_parse_cmd) >= 0
					&& ft_ch_buil(dt->ncmd, dt->l_parse_cmd) <= 6) || i == 0)
			{
				if (ft_execve (dt, dt->l_parse_cmd->id) == -1)
					return (-1);
			}
			else
				ft_exec_aux (i, dt);
			ft_free(dt, 0);
			dt->l_parse_cmd = dt->l_parse_cmd->next;
		}
	}
	else if (dt->l_parse_cmd == NULL && dt->l_parse_redir)
		ft_redir_null(dt);
	return (0);
}

void	ft_exec_aux(int i, t_in *dt)
{
	g_status = 127;
	if (i == -2)
		printf ("bash: %s: No such file or directory\n", dt->rootcmd);
	else
		printf ("bash: %s: command not found\n", dt->ncmd);
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
	char	builtins[7][7] = {"cd", "echo", "env", "exit", "export", "pwd", "unset"};
	int		i;

	i = -1;
	while (++i < 7)
	{
		if (ft_compare_str (name, builtins[i]) == 1)
		{
			list->type = 1;
			return (i);
		}
	}
	return (-1);
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

int	ft_ch_cmde_aux(t_in *dt)
{
	char	**root;
	char	*rootb;
	int		i;
	int		j;

	root = ft_cut_root(dt);
	i = -1;
	while (root[++i])
	{
		rootb = ft_strjoin(root[i], "/");
		free (root[i]);
		dt->rootcmd = ft_strjoin(rootb, dt->ncmd);
		free (rootb);
		if (access(dt->rootcmd, F_OK) == 0)
		{
			j = i;
			while (root[++j])
				free (root[j]);
			free (root);
			return (0);
		}
		ft_ch_cmde_aux_aux(dt);
	}
	free (root);
	return (-1);
}

void	ft_ch_cmde_aux_aux(t_in *dt)
{
	free (dt->rootcmd);
	dt->rootcmd = NULL;
}

char	*ft_get_name_bis(char *str)
{
	int		i;
	int		j;
	char	*strnew;

	i = 0;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '/')
			j = i;
	}
	j++;
	if (str[j] == 00)
	{
		return (NULL);
	}
	strnew = ft_strlcpy(str, j, (ft_strlen(str) - j));
	return (strnew);
}
