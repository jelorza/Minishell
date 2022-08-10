/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*       jelorza- <jelorza-@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:11:33 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/08/10 08:18:52 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_add_line(t_in *dt, char **rootold)
{
	int		j;
	char	**rootnew;

	j = 0;
	rootnew = NULL;
	if (rootold)
	{
		while (rootold[j])
			j++;
		rootnew = (char **) malloc(sizeof(char *) * (j + 2));
		j = -1;
		while (rootold[++j])
		{
			rootnew[j] = ft_strdup(rootold[j]);
			free (rootold[j]);
		}
		free (rootold);
	}
	else
		rootnew = (char **) malloc(sizeof(char *) * (2));
	rootnew[j] = ft_strdup(dt->env_value[ft_add_line_aux(dt)]);
	j++;
	rootnew[j] = NULL;
	return (rootnew);
}

int	ft_add_line_aux(t_in *dt)
{
	int	i;

	i = 0;
	while (dt->env_name[i] != NULL
		&& ft_compare_str(dt->env_name[i], "PWD") != 1)
		i++;
	return (i);
}

int	ft_ch_name_exist(t_in *dt, char *str)
{
	char	*name;
	int		i;

	name = ft_split_env_1(str);
	i = 0;
	while (dt->env_name[i])
	{
		if (ft_compare_str(name, dt->env_name[i]) == 1)
			break ;
		i++;
	}
	if (i != ft_strlen_bi(dt->env_name))
	{
		ft_change_value (dt, name, str);
		free (name);
		return (1);
	}
	else
	{
		free (name);
		return (0);
	}
}

void	ft_change_value(t_in *dt, char *name, char *str)
{
	int		i;
	char	*valuenew;
	char	*aux;

	i = 0;
	while (dt->env_name[i])
	{
		if (ft_compare_str(name, dt->env_name[i]) == 1)
			break ;
		i++;
	}
	valuenew = ft_split_env_2(str);
	free (dt->env_value[i]);
	dt->env_value[i] = ft_strdup(valuenew);
	free (valuenew);
	free (dt->env[i]);
	aux = ft_strjoin(name, "=");
	dt->env[i] = ft_strjoin(aux, dt->env_value[i]);
	free (aux);
}

char	**ft_update_env_plus(t_in *dt, char *str)
{
	char	**envnew;
	int		i;

	i = 0;
	while (dt->env[i])
		i++;
	envnew = (char **) malloc (sizeof(char *) * (i + 2));
	if (!envnew)
		return (NULL);
	i = -1;
	while (dt->env[++i])
	{
		envnew[i] = ft_strdup(dt->env[i]);
		free (dt->env[i]);
	}
	free (dt->env);
	envnew[i] = ft_strdup(str);
	envnew[++i] = NULL;
	return (envnew);
}
