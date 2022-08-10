/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*       jelorza- <jelorza-@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:11:33 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/08/10 08:16:03 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
