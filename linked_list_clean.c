/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_clean.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:07:54 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/21 11:08:25 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cleanListPipe(t_list **list)
{
	t_list	*aux;
	t_list	*next;

	aux = *list;
	while (aux != NULL)
	{
		next = aux->next;
		free(aux->data);
		free(aux);
		aux = next;
	}
	*list = NULL;
}

void	ft_cleanListRedir(t_list **list)
{
	t_list	*aux;
	t_list	*next;

	aux = *list;
	while (aux != NULL)
	{
		next = aux->next;
		free(aux->data);
		free(aux);
		aux = next;
	}
	*list = NULL;
}

void	ft_cleanListCmd(t_list **list)
{
	t_list	*aux;
	t_list	*next;

	aux = *list;
	while (aux != NULL)
	{
		next = aux->next;
		free(aux->data);
		free(aux);
		aux = next;
	}
	*list = NULL;
}
