/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/12 17:28:57 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin(t_in *dt, int n)
{
	int		i;

	i = n;
	i = ft_ch_buil(dt->ncmd, dt->l_parse_cmd);
	if (i == 0)
		ft_exe_cd(dt);
	if (i == 1)
		g_status = ft_exe_echo(dt, n);
	else if (i == 2)
		g_status = ft_exe_env(dt);
	else if (i == 3)
	{
		if (ft_exe_exit(dt) == -1)
			return (-1);
	}
	else if (i == 4)
		g_status = ft_exe_export(dt);
	else if (i == 5)
		g_status = ft_exe_pwd();
	else if (i == 6)
		g_status = ft_exe_unset(dt);
	return (0);
}

int	ft_exe_cd(t_in *dt)
{
	char	path[200];
	int		i;

	getcwd(path, 200);
	if (dt->cmdf[1])
	{
		if (ft_exe_cd_aux_aux(dt) == -1)
			return (-1);
		if (dt->nc != 1)
			chdir(path);
		else
		{
			ft_exe_cd_aux(dt);
			if (dt->cmdf[1][0] == '-')
				ft_exe_cd_print(dt);
		}
	}
	else if (dt->nc == 1)
	{
		i = ft_search_env (dt, "HOME");
		chdir(dt->env_value[i]);
		ft_exe_cd_aux(dt);
	}
	g_status = 0;
	return (0);
}

void	ft_exe_cd_print(t_in *dt)
{
	int	i;

	i = ft_search_env (dt, "PWD");
	printf ("%s\n", dt->env_value[i]);
}

int	ft_exe_cd_aux_aux(t_in *dt)
{
	int		fd;
	int		i;

	if (dt->cmdf[1][0] == '-')
	{
		i = ft_search_env (dt, "OLDPWD");
		chdir(dt->env_value[i]);
	}
	else if (chdir(dt->cmdf[1]) == -1)
	{
		fd = open(dt->cmdf[1], O_RDONLY);
		if (fd == -1)
			printf("bash: cd: %s: No such file or directory\n", dt->cmdf[1]);
		else
			printf("bash: cd: %s: Not a directory\n", dt->cmdf[1]);
		close (fd);
		g_status = 1;
		return (-1);
	}
	return (0);
}

void	ft_exe_cd_aux(t_in *dt)
{
	char	path[200];

	free (dt->rootold);
	dt->rootold = ft_strlcpy(dt->root, 0, ft_strlen(dt->root));
	free (dt->root);
	getcwd(path, 200);
	dt->root = ft_strlcpy(path, 0, ft_strlen(path));
	ft_env_act(dt);
}
