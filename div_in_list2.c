/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_in_list2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/27 18:56:16 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_redir_2(char *line, int i)
{
	if (line[i] == '>' && line[i + 1] == '>'
		&& line[i + 2] == '>' && line[i + 3] == '>')
	{
		printf("syntax error near unexpected token `%c%c' \n",
			line[i + 2], line[i + 3]);
		return (-1);
	}
	else if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
	{
		printf("syntax error near unexpected token `%c' \n", line[i + 2]);
		return (-1);
	}
	else if (line[i] == '<' && line[i + 1] == '<'
		&& line[i + 2] == '<' && line[i + 3] == '<'
		&& line[i + 4] == '<' && line[i + 5] == '<')
	{
		printf("syntax error near unexpected token `%c%c%c' \n",
			line[i + 2], line[i + 3], line[i + 4]);
		return (-1);
	}
	return (i);
}

int	ft_check_redir_3(char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<'
		&& line[i + 2] == '<' && line[i + 3] == '<' && line[i + 4] == '<')
	{
		printf("syntax error near unexpected token `%c%c' \n",
			line[i + 2], line[i + 3]);
		return (-1);
	}
	else if (line[i] == '<' && line[i + 1] == '<'
		&& line[i + 2] == '<' && line[i + 3] == '<')
	{
		printf("syntax error near unexpected token `%c' \n", line[i + 2]);
		return (-1);
	}
	return (i);
}
