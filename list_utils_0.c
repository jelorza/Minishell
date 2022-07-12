#include "minishell.h"

//funcion que crea nodos de la lista de redirecciones con el nombre del fichero, el comando al que afecta y el tipo de redireccion
t_list	*ft_new(char *file, int n, int t)
{
	t_list	*new;

	new = (t_list *) malloc (sizeof(t_list));
	if (new == NULL)
		return (NULL);
	if (file)
		new->data = ft_strlcpy(file, 0 , ft_strlen(file));
	else
		new->data = NULL;
	new->id = n;
	new->type = t;
	new->next = NULL;
	free (file);
	return (new);
}

void	ft_add_front(t_list **list, t_list *new)
{
	new->next = *list;
	*list = new;
}

void	ft_add_back(t_list **list, t_list *new)
{
	t_list	*aux;

	if (!*list)
		*list = new;
	else
	{
		aux = *list;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}

void	ft_print_list(t_list *list)
{
	t_list	*aux;
	int		i;

	i = 0;
	aux = list;
	while (aux)
	{
		printf ("El nodo %d:\nPertenece al comando: %d\nTipo: %d\nDato: %s\n", i, aux->id, aux->type, aux->data);
		aux = aux->next;
		i++;
	}
}

//tengo un leak por listireccion que haga en cada pipe, sigo para adelante y luego la buscare!!!
void	ft_destroy_list(t_list **list)
{
	t_list	*aux;
	t_list	*next;

	aux = *list;
	while (aux)
	{
		next = aux->next;
		free (aux->data);
		free (aux);
		aux = next;
	}
	*list = NULL;
}

int	ft_listlen (t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}
