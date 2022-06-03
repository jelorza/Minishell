#include "minishell.h"

t_pipes	*ft_newNod(char *data, t_pipes **list)
{
	static int id;
	t_pipes *new;

	if (*list == NULL)
		id = 0;
	new = malloc(sizeof(t_pipes));
	if (!new)
		return (0);
	new->id = id;
	new->data = ft_strdup(data);
	free(data);
	new->next = NULL;
	id++;
	return(new);

}

void	ft_addNodBack(t_pipes **list, char *data)
{
	t_pipes *new;
	t_pipes *aux;

	aux = *list;
	new = ft_newNod(data,list);
	if(!new)
		return ;
	if (aux == NULL)
		*list = new;
	else
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}

void	ft_addNodFront(t_pipes **list, char *data)
{
	t_pipes *new;

	new = ft_newNod(data,list);
	if (*list)
		new->next = *list;
	*list = new;
}

void	ft_printList(t_pipes **list)
{	
	if (*list)
	{
		t_pipes *aux;
		aux = *list;
		while(aux != NULL)
		{	
			printf("nodo %d -> %s\n",aux->id, aux->data);
			aux = aux->next;
		}
	}
	else
		printf("La lista esta vacia\n");
}

void	ft_cleanList(t_pipes **list)
{
	t_pipes *aux;
	t_pipes *next;

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
