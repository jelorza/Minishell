/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 09:46:34 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/21 11:07:35 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_nod_back_re(t_in *dt, char *data, int id, char list)
{
	t_list	*new;
	t_list	*aux;

	new = ft_newNodRe(data, &dt->l_parseRedir, id, list);
	aux = dt->l_parseRedir;
	if (!new)
		return ;
	if (aux == NULL)
		dt->l_parseRedir = new;
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

	new = ft_newNodPi(data, &dt->l_parseInit);
	aux = dt->l_parseInit;
	if (!new)
		return ;
	if (aux == NULL)
		dt->l_parseInit = new;
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

	new = ft_newNodCmd(data, &dt->l_parseCmd, id);
	aux = dt->l_parseCmd;
	if (!new)
		return ;
	if (aux == NULL)
		dt->l_parseCmd = new;
	else
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}

void	ft_addNodBack(t_in *dt, char *data, char list, int id)
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
