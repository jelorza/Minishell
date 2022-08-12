/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/12 17:09:47 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_quot_re(char *str)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	j = 0;
	aux = malloc (sizeof(char *) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] != 1)
			aux[j++] = str[i];
		i++;
	}
	aux[j] = 00;
	free (str);
	return (aux);
}

void	ft_clean_redir(t_in *dt)
{
	t_list	*aux;
	t_list	*aux2;

	aux = dt->l_parse_redir;
	aux2 = dt->l_parse_redir;
	while (aux)
	{
		dt->l_parse_redir->data = ft_remove_quot_re(dt->l_parse_redir->data);
		aux = aux->next;
		dt->l_parse_redir = dt->l_parse_redir->next;
	}
	dt->l_parse_redir = aux2;
}
