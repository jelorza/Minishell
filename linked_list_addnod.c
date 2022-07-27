/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_addnod.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/27 12:19:19 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_nod_back_re(t_in *dt, char *data, int id, char list)
{
	t_list	*new;
	t_list	*aux;

	new = ft_new_nod_re(data, &dt->l_parse_redir, id, list);
	aux = dt->l_parse_redir;
	if (!new)
		return ;
	if (aux == NULL)
		dt->l_parse_redir = new;
	else
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}

void	ft_add_nod_back_pipe(t_in *dt, char *data)
{
	t_list	*new;
	t_list	*aux;

	new = ft_new_nod_pi(data, &dt->l_parse_init);
	aux = dt->l_parse_init;
	if (!new)
		return ;
	if (aux == NULL)
		dt->l_parse_init = new;
	else
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}

void	ft_add_nod_back_cmd(t_in *dt, char *data, int id)
{
	t_list	*new;
	t_list	*aux;

	new = ft_new_nod_cmd(data, &dt->l_parse_cmd, id);
	aux = dt->l_parse_cmd;
	if (!new)
		return ;
	if (aux == NULL)
		dt->l_parse_cmd = new;
	else
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}

void	ft_add_nod_back(t_in *dt, char *data, char list, int id)
{
	if (list == 'p')
		ft_add_nod_back_pipe(dt, data);
	else if (list == '1' || list == '2' || list == '3' || list == '4')
		ft_add_nod_back_re(dt, data, id, list);
	else if (list == 'c')
		ft_add_nod_back_cmd(dt, data, id);
	else
		printf("Redireccion sin controlar\n");
}
