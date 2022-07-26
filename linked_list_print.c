/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/26 11:09:36 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_list_cmd(t_list **list)
{	
	t_list	*aux;

	if (*list)
	{
		aux = *list;
		while (aux != NULL)
		{	
			printf("nodo %s pertenece a %d\n", aux->data, aux->id);
			aux = aux->next;
		}
	}
	else
		printf("La lista esta vacia\n");
}

void	ft_print_list_redir(t_list **list)
{	
	t_list	*aux;

	if (*list)
	{
		aux = *list;
		while (aux != NULL)
		{	
			printf("nodo %s pertenece a %d y es de tipo %d\n", aux->data,
				aux->id, aux->type);
			aux = aux->next;
		}
	}
	else
		printf("La lista esta vacia\n");
}

void	ft_print_list_pipe(t_list **list)
{	
	t_list	*aux;

	if (*list)
	{
		aux = *list;
		while (aux != NULL)
		{	
			printf("nodo %d -> %s\n", aux->id, aux->data);
			aux = aux->next;
		}
	}
	else
		printf("La lista esta vacia\n");
}
