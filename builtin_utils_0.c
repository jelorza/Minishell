/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_utils_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/26 12:07:54 by jelorza-         ###   ########.fr       */
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

//funcion que imprime el env
int	ft_exe_env(t_in *dt)
{
	int	i;

	i = -1;
	while (dt->env[++i])
		printf ("%s\n", dt->env[i]);
	return (0);
}

int	ft_exe_exit(t_in *dt)
{
	long	aux;

	aux = 0;
	if (ft_strlen_bi(dt->cmdf) > 2)
	{
		g_status = 1;
		if (dt->nc == 1)
			printf ("exit\n");
		printf ("bash: exit: too many arguments\n");
		return (0);
	}
	if (dt->cmdf[1])
	{
		aux = ft_atoi(dt->cmdf[1]);
		if (ft_exe_exit_aux(dt, aux) == -1)
			return (-1);
	}
	if (dt->nc == 1)
	{
		if (g_status == -1)
			g_status = 0;
		printf ("exit\n");
		return (-1);
	}
	return (0);
}

int	ft_exe_exit_aux(t_in *dt, long aux)
{
	if (aux == -1)
	{
		g_status = 1;
		if (dt->nc == 1)
			printf ("exit\n");
		printf ("bash: exit: %s: numeric argument required\n", dt->cmdf[1]);
		if (dt->nc == 1)
			return (-1);
	}
	if (aux > 256)
		aux = aux % 256;
	g_status = aux;
	return (0);
}

//funcionpara el pwd
int	ft_exe_pwd(void)
{
	char	path[200];

	if (getcwd(path, 200) == NULL)
	{
		g_status = 1;
		return (-1);
	}
	printf ("%s\n", path);
	g_status = 0;
	return (g_status);
}

//funcion del export
int	ft_exe_export(t_in *dt)
{
	int	i;
	int	j;

	i = 0;
	while (dt->cmdf[++i])
	{
		j = ft_ch_name(dt->cmdf[i], 'e');
		if (j == 1)
		{
			printf ("bash: export: `%s': not a valid identifier\n", dt->cmdf[i]);
			g_status = 1;
		}
		else if (j == 0)
		{
			if (ft_ch_name_exist(dt, dt->cmdf[i]) == 0)
			{
				dt->env = ft_update_env_plus(dt, dt->cmdf[i]);
				dt->env_name = ft_update_env_aux(dt, 'n');
				dt->env_value = ft_update_env_aux(dt, 'v');
			}
		}
	}
	if (g_status == 1)
		return (1);
	return (0);
}

int	ft_ch_name(char *str, char c)
{
	int	i;

	if (!(str[0] >= 65 && str[0] <= 90) && !(str[0] >= 97 && str[0] <= 122))
	{
		if (str[0] != 95)
			return (1);
	}
	i = 0;
	while (str[++i] && str[i] != '=')
	{
		if ((str[i] >= 0 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 64)
			|| (str[i] >= 91 && str[i] <= 96)
			|| (str[i] >= 123 && str[i] <= 127))
		{
			if (str[i] != 95)
				return (1);
		}
	}
	if (c == 'e' && !str[i])
		return (2);
	if (c == 'u' && str[i] == '=')
		return (1);
	return (0);
}

int	ft_exe_unset(t_in *dt)
{
	int		i;

	i = 0;
	while (dt->cmdf[++i])
	{
		if (ft_ch_name(dt->cmdf[i], 'u') == 1)
		{
			printf ("bash: unset: `%s': not a valid identifier\n", dt->cmdf[i]);
			g_status = 1;
		}
		else
		{
			if (ft_ch_name_exist_bis(dt, dt->cmdf[i]) == 1)
			{
				dt->env = ft_update_env_minus(dt, dt->cmdf[i]);
				dt->env_name = ft_update_env_aux(dt, 'n');
				dt->env_value = ft_update_env_aux(dt, 'v');
			}
		}
	}
	if (g_status == 1)
		return (1);
	return (0);
}
