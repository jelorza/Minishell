/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:08:34 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/21 11:09:02 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printListCmd(t_list **list)
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

void	ft_printListRedir(t_list **list)
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

void	ft_printListPipe(t_list **list)
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
