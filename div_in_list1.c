/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_in_list1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/12 17:04:22 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_div_in_lists(t_in *dt)
{
	int		ret;
	t_list	*aux;
	char	type;

	type = 00;
	if (dt->l_parse_init)
	{
		aux = dt->l_parse_init;
		while (aux != NULL)
		{
			ret = ft_check_and_create(aux->data, dt, aux->id, type);
			aux = aux->next;
			if (ret == 0)
			{
				ft_clean_all_lists(dt);
				break ;
			}
		}
	}
}

int	ft_check_and_create(char *line, t_in *dt, int id, char type)
{
	int		c[2];

	c[0] = 0;
	while (line[c[0]])
	{
		c[0] = ft_del_spaces(line, c[0]);
		c[1] = c[0];
		if (line[c[0]] && (line[c[0]] == '<' || line[c[0]] == '>'))
		{
			type = ft_redir_type(line, c[0]);
			c[0] = ft_check_create0(line, c[0], type);
			if (c[0] == -1)
				return (0);
			else if (c[0] == -2)
				break ;
			c[1] = c[0];
			c[0] = ft_check_create1(line, c[0]);
			if (c[0] == -1)
				return (0);
			ft_add_nod_back(dt, ft_substr(line, c[1], c[0]), type, id);
		}
		else if (line[c[0]] && line[c[0]] != '<' && line[c[0]] != '>')
			c[0] = ft_check_create3(line, c, id, dt);
	}
	return (1);
}

int	ft_del_spaces(char *line, int c)
{
	while (line[c] && line[c] == ' '
		&& ft_count_rarus(line, c) == 0)
		c++;
	return (c);
}

char	ft_redir_type(char *line, int i)
{
	int	z;

	z = i;
	i = ft_check_redir_1(line, i);
	if (i == -1)
		return ('5');
	i = z;
	i = ft_check_redir_2(line, i);
	if (i == -1)
		return ('5');
	i = ft_check_redir_3(line, i);
	if (i == -1)
		return ('5');
	else if (line[i] == '<' && line[i + 1] != '<')
		return ('1');
	else if (line[i] == '>' && line[i + 1] != '>')
		return ('2');
	else if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
		return ('6');
	else if (line[i] == '<' && line[i + 1] == '<')
		return ('3');
	else if (line[i] == '>' && line[i + 1] == '>')
		return ('4');
	else
		return (0);
}

int	ft_check_redir_1(char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '>')
	{
		printf("syntax error near unexpected token `%c' \n", line[i]);
		return (-1);
	}
	else if (line[i] == '>' && line[i + 1] == '<')
	{
		printf("syntax error near unexpected token `%c' \n", line[i]);
		return (-1);
	}
	i++;
	if (line[i] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '<' || line[i] == '>')
		{
			printf("syntax error near unexpected token `%c' \n", line[i]);
			return (-1);
		}
	}
	return (1);
}
