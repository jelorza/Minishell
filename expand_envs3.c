/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/28 11:54:16 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_cases(char *line)
{
	int	bo1;
	int	i;

	bo1 = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '"' && line[i + 1] != '"')
		{
			while (line[++i] != '"' && line[i])
			{
				if (line[i] == '$')
				{
					bo1 = 1;
					return (bo1);
				}
			}
		}
	}
	return (bo1);
}

char	*ft_case_1(char *line, char *old, char *new, int c[2])
{
	char	*r;

	r = malloc(1 * (ft_strlen(line) - ft_strlen(old) + ft_strlen(new)) + 1);
	while (line[c[0]])
	{
		if (line[c[0]] == '"' && line[c[0] + 1] != '"')
		{
			r[c[1]++] = line[c[0]++];
			while (line[c[0]] != '"' && line[c[0]])
			{
				if (line[c[0]] == '$')
				{
					r = ft_replace_if_env(line, c, new, r);
					free(line);
					r[c[1]] = 00;
					return (r);
				}
				else
					r[c[1]++] = line[c[0]++];
			}
		}
		else
			r[c[1]++] = line[c[0]++];
	}
	return (NULL);
}

char	*ft_case_2(char *line, char *old, char *new, int c[2])
{
	char	*r;

	r = malloc(1 * (ft_strlen(line) - ft_strlen(old) + ft_strlen(new)) + 1);
	while (line[c[0]])
	{
		if (line[c[0]] == 39)
		{
			r[c[1]++] = line[c[0]];
			while (line[++c[0]] != 39 && line[c[0]])
				r[c[1]++] = line[c[0]];
		}
		if (line[c[0]] == '$')
		{
			r = ft_replace_if_env(line, c, new, r);
			break ;
		}
		else
			r[c[1]++] = line[c[0]++];
	}
	free (line);
	r[c[1]] = 00;
	return (r);
}

char	*ft_replace_in_line(char *line, char *old, char *new)
{
	int	caso;
	int	c[2];

	c[0] = 0;
	c[1] = 0;
	caso = ft_check_cases(line);
	if (caso == 1)
		return (ft_case_1(line, old, new, c));
	else if (caso == 0)
		return (ft_case_2(line, old, new, c));
	return (line);
}
