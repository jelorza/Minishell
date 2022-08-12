/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/12 12:50:20 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_replace_if_env(char *line, int *c, char *new, char *result)
{
	int	z;

	z = 0;
	while (new[z])
	{
		result[c[1]] = new[z];
		c[1]++;
		z++;
	}
	while (line[c[0]] != ' ' && line[c[0]] && line[c[0]] != '"'
		&& line[c[0]] != 39)
	{
		c[0]++;
		if (line[c[0]] == '$')
			break ;
	}
	while (line[c[0]])
	{
		result[c[1]] = line[c[0]];
		c[0]++;
		c[1]++;
	}
	result[c[1]] = 00;
	return (result);
}

int	ft_check_in_env_list(char *env, t_in *dt)
{
	int	i;

	i = -1;
	while (dt->env_name[++i])
	{
		if (ft_compare_str(env, dt->env_name[i]))
			return (i);
	}
	return (0);
}

char	*ft_strdup_spacial(char *str)
{
	int		i;
	int		j;
	char	*st;
	char	*aux;

	i = -1;
	st = ft_itoa(g_status);
	aux = malloc (sizeof(char *) * (ft_strlen(str) + ft_strlen(st)));
	while (st[++i])
		aux[i] = st[i];
	j = 0;
	while (str[++j])
	{
		aux[i] = str[j];
		i++;
	}
	aux[i] = 00;
	free (st);
	return (aux);
}

void	ft_cmp_replace(char *env[3], t_in *dt, int is_env)
{
	char	*st;

	if (env[0][0] == '?' && env[0][1] && env[0][1] != ' ')
		env[2] = ft_replace_in_line(env[2], env[0], ft_strdup_spacial(env[0]));
	else if (!ft_compare_str(env[0], "?"))
	{
		is_env = ft_check_in_env_list(env[0], dt);
		env[1] = ft_strdup(dt->env_value[is_env]);
		env[2] = ft_replace_in_line(env[2], env[0], env[1]);
		free(env[1]);
	}
	else
	{
		st = ft_itoa(g_status);
		env[2] = ft_replace_in_line(env[2], env[0], st);
		free(st);
	}
}
