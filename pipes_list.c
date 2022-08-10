/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/10 18:34:27 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipes_list(char *line, t_in *dt, int i, int z)
{
	i = ft_init(line, i = 0);
	if (i == -1)
		return (0);
	while (i < ft_strlen(line))
	{
		while (line[i] != '|' && line[i])
		{
			i = ft_check_quotations(line, i);
			if (i++ == -1)
				return (-1);
			if (line[i] == '|' && line[i + 1] == '|')
				break ;
		}
		if (line[i] == '|' && (line[i + 1] == ' ' || line[i + 1] == '|'))
		{
			i = ft_check_pipe(line, i);
			if (i == -1)
				return (0);
		}
		i = ft_create_new(line, z, i, dt);
		z = i;
	}
	return (0);
}

int	ft_init(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (-1);
	}
	return (i);
}

int	ft_check_quotations(char *line, int i)
{
	if (line[i] == 39)
	{
		i = ft_check_quot(line, i, '1');
		if (i == -1)
			return (-1);
	}
	else if (line[i] == '"')
	{
		i = ft_check_quot(line, i, '2');
		if (i == -1)
			return (-1);
	}
	return (i);
}

int	ft_check_quot(char *line, int i, char type)
{
	if (type == '1')
		type = 39;
	else
		type = '"';
	if (line[++i])
	{
		while ((line[i] != type) && line[i])
			i++;
	}
	if (!line[i])
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	return (i);
}

int	ft_check_pipe(char *line, int i)
{
	int	c;

	c = i;
	i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (-1);
	}
	else
		i = c;
	return (i);
}
