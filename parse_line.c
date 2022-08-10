/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/10 15:03:57 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_line(char *line, t_in *dt)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	line = ft_expand_envs(line, dt);
	if (ft_pipes_list(line, dt, i, z) == -1)
	{
		free (line);
		return (0);
	}
	ft_remove_quot(dt);
	ft_div_in_lists(dt);
	free (line);
	if (ft_exec(dt) == -1)
		return (-1);
	return (0);
}	

int	ft_put_noimp(t_in *dt, int i)
{
	t_list	*aux;

	aux = dt->l_parse_init;
	while (aux->data[i])
	{
		if (aux->data[i] == '"' )
		{
			dt->l_parse_init->data[i] = '!';
			while (aux->data[++i] != '"' && aux->data[i])
				dt->l_parse_init->data[i] = aux->data[i];
			dt->l_parse_init->data[i] = '!';
		}
		else if (aux->data[i] == 39)
		{
			dt->l_parse_init->data[i] = '!';
			while (aux->data[++i] != 39 && aux->data[i])
				dt->l_parse_init->data[i] = aux->data[i];
			dt->l_parse_init->data[i] = '!';
		}
		else
			dt->l_parse_init->data[i] = aux->data[i];
		i++;
	}
	return (0);
}

void	ft_remove_quot(t_in *dt)
{
	int		i;
	t_list	*aux;
	t_list	*aux2;

	aux = dt->l_parse_init;
	aux2 = dt->l_parse_init;
	while (aux)
	{
		i = 0;
		i = ft_put_noimp(dt, i);
		aux = aux->next;
		dt->l_parse_init = dt->l_parse_init->next;
		i = 0;
	}
	dt->l_parse_init = aux2;
}

int	ft_create_new(char *line, int z, int i, t_in *dt)
{
	char	*data;

	data = ft_substr(line, z, i);
	ft_add_nod_back(dt, data, 'p', 0);
	if (line[i] == '|' && line[i + 1] != '|')
		i++;
	else
	{
		while (line[i])
			i++;
	}
	return (i);
}

void	ft_print_all_lists(t_in *dt)
{
	printf("Lista de pipe\n");
	ft_print_list_pipe(&dt->l_parse_init);
	printf("Lista de cmd\n");
	ft_print_list_cmd(&dt->l_parse_cmd);
	printf("Lista de redir\n");
	ft_print_list_redir(&dt->l_parse_redir);
}
