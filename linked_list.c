#include "minishell.h"

t_list	*ft_newNodCmd(char *data, t_list **list, int id)
{
	t_list *new;
	list = NULL;
	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->id = id;
	new->data = ft_strdup(data);
	new->type = 0;
	free(data);
	new->next = NULL;
	return(new);
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
	return(new);
}

t_list	*ft_newNodPi(char *data, t_list **list)
{
	static int id;
	t_list *new;

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
	return(new);
}

void	ft_addNodBack(t_in *dt, char *data, char list, int id)
{
	if (list == 'p') // lista de pipes.
	{
		t_list *new;
		t_list *aux;
		new = ft_newNodPi(data,&dt->l_parseInit);
		aux = dt->l_parseInit;
	
		if(!new)
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
	else if (list == '1' || list == '2' || list == '3' || list == '4') // lista de comandos.
	{
		t_list *new;
		t_list *aux;
		new = ft_newNodRe(data,&dt->l_parseRedir, id, list);
		aux = dt->l_parseRedir;

		if(!new)
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
	else if (list == 'c')
	{
		t_list *new;
		t_list *aux;
		new = ft_newNodCmd(data,&dt->l_parseCmd, id);
		aux = dt->l_parseCmd;
		if(!new)
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
	else
		printf("Redireccion sin controlar\n");
}

void	ft_printListCmd(t_list **list)
{	
	if (*list)
	{
		t_list *aux;
		aux = *list;
		while(aux != NULL)
		{	
			printf("nodo %s pertenece a %d\n", aux->data, aux->id );
			aux = aux->next;
		}
	}
	else
		printf("La lista esta vacia\n");
}

void	ft_printListRedir(t_list **list)
{	
	if (*list)
	{
		t_list *aux;
		aux = *list;
		while(aux != NULL)
		{	
			printf("nodo %s pertenece a %d y es de tipo %d\n", aux->data, aux->id, aux->type);
			aux = aux->next;
		}
	}
	else
		printf("La lista esta vacia\n");
}

void	ft_printListPipe(t_list **list)
{	
	if (*list)
	{
		t_list *aux;
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

void	ft_cleanListPipe(t_list **list)
{
	t_list *aux;
	t_list *next;

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
	t_list *aux;
	t_list *next;

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
	t_list *aux;
	t_list *next;

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
