/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_in_list3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/27 18:56:30 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_create0(char *line, int i, char type)
{
	if (type == '3' || type == '4')
		i++;
	else if (type == '5')
		return (-1);
	else if (type == '6')
		return (-2);
	i++;
	if (line[i] == ' ')
	{
		while (line[i] == ' ' && line[i])
		i++;
	}
	return (i);
}

int	ft_check_create1(char *line, int i)
{
	if (line[i] == '>')
	{
		printf("syntax error near unexpected token`%c'\n", line[i]);
		return (-1);
	}
	while (line[i] != ' ' && line[i])
	{
		i = ft_check_quotations(line, i);
		if (i == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_check_create2(char *line, int i)
{
	while (line[i] != '>' && line[i] != '<'
		&& line[i] && line[i] != ' ')
	{
		i = ft_check_quotations(line, i);
		if (i == -1)
			return (-1);
		i++;
	}
	if (line[i])
		i++;
	return (i);
}

int	ft_check_create3(char *line, int c[2], int id, t_in *dt)
{
	char	*data;

	c[0] = ft_check_create2(line, c[0]);
	data = ft_substr(line, c[1], c[0]);
	if (dt -> l_parse_cmd == NULL
		|| ft_check_create4(dt, 0, data) != id)
		ft_add_nod_back(dt, data, 'c', id);
	else
		ft_check_create4(dt, 1, data);
	return (c[0]);
}

int	ft_check_create4(t_in *dt, int bool, char *data)
{
	t_list	*aux;
	int		ret;

	aux = dt -> l_parse_cmd;
	ret = 0;
	if (aux ->next)
	{
		while (aux -> next != NULL)
			aux = aux->next;
	}
	if (bool == 1)
		aux -> data = ft_strjoin_aux(aux -> data, data);
	ret = aux -> id;
	return (ret);
}
