#include "minishell.h"

t_pipes	*ft_newNod(char *data)
{
	static int id;
	t_pipes *new;

	//estoy pensando en meter un bool para saber si es un comando nuevo o no para resetear la variable statica.

	new = malloc(sizeof(t_pipes));
	if (!new)
		return (0);
	new->id = id;
	new->data = data;
	new->next = NULL;
	id++;
	return(new);

}

void	ft_addNodBack(t_pipes **l_list, char *data)
{
	t_pipes *new;
	t_pipes *aux;

	aux = *l_list;
	new = ft_newNod(data);
	if(!new)
		return ;
	if (aux == NULL)
		*l_list = new;
	else
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}

void	ft_addNodFront(t_pipes **l_list, char *data)
{
	t_pipes *new;

	new = ft_newNod(data);
	if (*l_list)
		new->next = *l_list;
	*l_list = new;
}

void	ft_printList(t_pipes **list)
{	
	printf("desde print\n");
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
