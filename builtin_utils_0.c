/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/10 08:16:58 by pojea-lo         ###   ########.fr       */
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

int	ft_exe_echo(t_in *dt, int n)
{
	int	i;

	i = 1;
	n = 0;
	if (dt->cmdf[1] && ft_compare_str(dt->cmdf[1], "-n"))
	{
		n = 1;
		i++;
	}
	while (dt->cmdf[i])
	{
		printf("%s", dt->cmdf[i]);
		i++;
		if (dt->cmdf[i])
			printf(" ");
	}
	if (n == 0)
		printf("\n");
	return (0);
}

int	ft_exe_cd(t_in *dt)
{
	char	path[200];
	int		fd;

	getcwd(path, 200);
	if (dt->cmdf[1])
	{
		if (chdir(dt->cmdf[1]) == -1)
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
		if (dt->nc != 1)
			chdir(path);
		else
			ft_exe_cd_aux(dt);
	}
	g_status = 0;
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

int	ft_exe_env(t_in *dt)
{
	int	i;

	i = -1;
	while (dt->env[++i])
		printf ("%s\n", dt->env[i]);
	return (0);
}
