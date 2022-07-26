/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_clean.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/26 11:06:54 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_list_pipe(t_list **list)
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

void	ft_clean_list_redir(t_list **list)
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

void	ft_clean_list_cmd(t_list **list)
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
