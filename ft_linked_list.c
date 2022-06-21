#include "minishell.h"

t_rest	*ft_newNodRest(char *data, t_rest **list, int id)
{
	t_rest *new;
	list = NULL;
	new = malloc(sizeof(t_rest));
	if (!new)
		return (0);
	new->id = id;
	new->data = ft_strdup(data);
	free(data);
	new->next = NULL;
	return(new);
}

t_cmd	*ft_newNodCmd(char *data, t_cmd **list, int id)
{
	t_cmd *new;
	list = NULL;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->id = id;
	new->data = ft_strdup(data);
	free(data);
	new->next = NULL;
	return(new);
}

t_redir	*ft_newNodRe(char *data, t_redir **list, int id, char type)
{
	t_redir *new;


	new = malloc(sizeof(t_redir));
	list = NULL;
	if (!new)
		return (0);
	new->id = id;
	new->type = type;
	new->data = ft_strdup(data);
	free(data);
	new->next = NULL;
	return(new);
}

t_pipes	*ft_newNodPi(char *data, t_pipes **list)
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

void	ft_addNodBack(t_struct *structInit, char *data, char list, int id)
{
	if (list == 'p') // lista de pipes.
	{
		t_pipes *new;
		t_pipes *aux;
		new = ft_newNodPi(data,&structInit->l_parseInit);
		aux = structInit->l_parseInit;
	
		if(!new)
			return ;
		if (aux == NULL)
			structInit->l_parseInit = new;
		else
		{
			while (aux->next != NULL)
				aux = aux->next;
			aux->next = new;
		}
	}
	else if (list == '1' || list == '2' || list == '3' || list == '4') // lista de comandos.
	{
		t_redir *new;
		t_redir *aux;
		new = ft_newNodRe(data,&structInit->l_parseRedir, id, list);
		aux = structInit->l_parseRedir;

		if(!new)
			return ;
		if (aux == NULL)
			structInit->l_parseRedir = new;
		else
		{
			while (aux->next != NULL)
				aux = aux->next;
			aux->next = new;
		}
		
	}
	else if (list == 'c')
	{
		t_cmd *new;
		t_cmd *aux;
		new = ft_newNodCmd(data,&structInit->l_parseCmd, id);
		aux = structInit->l_parseCmd;
		if(!new)
			return ;
		if (aux == NULL)
			structInit->l_parseCmd = new;
		else
		{
			while (aux->next != NULL)
				aux = aux->next;
			aux->next = new;
		}
	}
	else if (list == 's')
	{
		t_rest *new;
		t_rest *aux;
		new = ft_newNodRest(data,&structInit->l_parseRest, id);
		aux = structInit->l_parseRest;
		if(!new)
			return ;
		if (aux == NULL)
			structInit->l_parseRest = new;
		else
		{
			while (aux->next != NULL)
				aux = aux->next;
			aux->next = new;
		}
	}
	else
		printf("mierda\n");
}


void	ft_printListRest(t_rest **list)
{	
	if (*list)
	{
		t_rest *aux;
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


void	ft_printListCmd(t_cmd **list)
{	
	if (*list)
	{
		t_cmd *aux;
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

void	ft_printListRedir(t_redir **list)
{	
	if (*list)
	{
		t_redir *aux;
		aux = *list;
		while(aux != NULL)
		{	
			printf("nodo %s pertenece a %d y es de tipo %c\n", aux->data, aux->id, aux->type);
			aux = aux->next;
		}
	}
	else
		printf("La lista esta vacia\n");
}

void	ft_printListPipe(t_pipes **list)
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

void	ft_cleanListRest(t_rest **list)
{
	t_rest *aux;
	t_rest *next;

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

void	ft_cleanListPipe(t_pipes **list)
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

void	ft_cleanListRedir(t_redir **list)
{
	t_redir *aux;
	t_redir *next;

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

void	ft_cleanListCmd(t_cmd **list)
{
	t_cmd *aux;
	t_cmd *next;

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
