/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/12 12:50:17 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_envs(char *line, t_in *dt)
{
	char	*env[3];
	int		is_env;
	int		n;

	env[2] = ft_strdup(line);
	is_env = 0;
	n = ft_char_counter(line, '$');
	while (n > 0)
	{
		env[0] = ft_check_env(env[2]);
		if (ft_check_in_env_list(env[0], dt) || env[0][0] == '?')
			ft_cmp_replace(env, dt, is_env);
		else
			env[2] = ft_replace_in_line(env[2], env[0], " ");
		free(env[0]);
		n--;
	}
	return (env[2]);
}

int	ft_char_counter(char *line, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < ft_strlen(line))
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] != '"' && line[i])
			{	
				if (line[i] == c && line[i + 1] && line[i + 1]
					!= '"' && line[i + 1] != 39)
					count++;
				i++;
			}
		}
		i = ft_check_if39(line, i);
		if (line[i] == c && line[i + 1] && line[i + 1]
			!= '"' && line[i + 1] != 39)
			count++;
	}
	return (count);
}

int	ft_check_if39(char *line, int i)
{
	if (line[i] == 39)
	{
		i++;
		while (line[i] != 39 && line[i])
			i++;
	}
	return (i);
}

char	*ft_check_env(char *line)
{
	int	i;
	int	z;

	i = -1;
	z = 0;
	while (line[++i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] != '"' && line[i])
			{	
				if (line[i] == '$')
					return (ft_check_if_env(line, i));
				i++;
			}
		}
		i = ft_check_if39(line, i);
		if (line[i] == '$')
			return (ft_check_if_env(line, i));
	}
	return (NULL);
}

char	*ft_check_if_env(char *line, int i)
{
	char	*env;
	int		z;

	i++;
	z = i;
	while (line[i] != ' ' && line[i] != '$' && line[i] && line[i] != 39
		&& line[i] != '"')
		i++;
	if (line[i - 1] == '"' || line[i - 1] == 39)
	{
		if (line[i - 2] == 39)
			i--;
		i--;
	}
	env = ft_substr(line, z, i);
	return (env);
}
