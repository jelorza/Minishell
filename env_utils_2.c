/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*       jelorza- <jelorza-@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:11:33 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/08/10 08:19:07 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ch_name_exist_bis(t_in *dt, char *str)
{
	char	*name;
	int		i;

	name = ft_split_env_1(str);
	i = -1;
	while (dt->env_name[++i])
	{
		if (ft_compare_str(name, dt->env_name[i]) == 1)
			break ;
	}
	if (i != ft_strlen_bi(dt->env_name))
	{
		free (name);
		return (1);
	}
	free (name);
	return (0);
}

char	**ft_update_env_minus(t_in *dt, char *str)
{
	char	**envnew;
	char	*name;
	int		i;
	int		j;

	name = ft_split_env_1(str);
	envnew = (char **) malloc (sizeof(char *) * (ft_strlen_bi(dt->env)));
	i = -1;
	while (ft_compare_str(name, dt->env_name[++i]) != 1)
	{
		envnew[i] = ft_strdup(dt->env[i]);
		free (dt->env[i]);
	}
	free (dt->env[i]);
	dt->env[i] = NULL;
	j = i;
	while (dt->env[++j])
	{
		envnew[i++] = ft_strdup(dt->env[j]);
		free (dt->env[j]);
	}
	envnew[i] = NULL;
	free (dt->env);
	free (name);
	return (envnew);
}

char	**ft_update_env_aux(t_in *dt, char c)
{
	int		i;
	char	**env_new;

	i = ft_update_env_aux_aux(dt, c);
	env_new = (char **) malloc (sizeof(char *) * (i + 2));
	i = -1;
	while (dt->env[++i] != NULL)
	{
		if (c == 'n')
			env_new[i] = ft_split_env_1(dt->env[i]);
		else if (c == 'v')
			env_new[i] = ft_split_env_2(dt->env[i]);
	}
	env_new[i] = NULL;
	return (env_new);
}

int	ft_update_env_aux_aux(t_in *dt, char c)
{
	int	i;

	i = -1;
	if (c == 'n')
	{
		while (dt->env_name[++i] != NULL)
			free(dt->env_name[i]);
		free (dt->env_name);
	}
	if (c == 'v')
	{
		while (dt->env_value[++i] != NULL)
			free(dt->env_value[i]);
		free (dt->env_value);
	}
	return (i);
}
