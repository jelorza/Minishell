/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_newnod.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:09:14 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/21 11:09:41 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_newNodCmd(char *data, t_list **list, int id)
{
	t_list	*new;

	list = NULL;
	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->id = id;
	new->data = ft_strdup(data);
	free(data);
	new->next = NULL;
	return (new);
}

t_list	*ft_newNodRe(char *data, t_list **list, int id, char type)
{
	t_list	*new;
	int		n;

	if (type == '1')
		n = 1;
	if (type == '2')
		n = 2;
	if (type == '3')
		n = 3;
	if (type == '4')
		n = 4;
	new = malloc(sizeof(t_list));
	list = NULL;
	if (!new)
		return (0);
	new->id = id;
	new->type = n;
	new->data = ft_strdup(data);
	free(data);
	new->next = NULL;
	return (new);
}

t_list	*ft_newNodPi(char *data, t_list **list)
{
	static int	id;
	t_list		*new;

	if (*list == NULL)
		id = 0;
	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->id = id;
	new->data = ft_strdup(data);
	new->type = 0;
	free(data);
	new->next = NULL;
	id++;
	return (new);
}
