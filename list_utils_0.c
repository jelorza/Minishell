#include "minishell.h"

//funcion que crea nodos de la lista de redirecciones con el nombre del fichero, el comando al que afecta y el tipo de redireccion
t_list	*ft_new(char *file, int n, int t)
{
	t_list	*new;

	new = (t_list *) malloc (sizeof(t_list));
	if (new == NULL)
		return (NULL);
	if (file)
		new->file = ft_strlcpy(file, 0 , ft_strlen(file));
	else
		new->file = NULL;
	new->id = n;
	new->t = t;
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

	if (*list == NULL)
		*list = new;
	else
	{
		aux = *list;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}

void	ft_print_list(t_list **list)
{
	t_list	*aux;
	int		i;

	i = 0;
	aux = *list;
	while (aux->next != NULL)
	{
		printf ("El nodo %d:\nPertenece al comando: %d\nTipo de redireccion: %d\nNombre del file: %s\n", i, aux->id, aux->t, aux->file);
		aux = aux->next;
		i++;
	}
	printf ("El nodo %d:\nPertenece al comando: %d\nTipo de redireccion: %d\nNombre del file: %s\n", i, aux->id, aux->t, aux->file);
}

void	ft_destroy_list(t_in *dt)
{
	int	c;//cuento los nodos de la lista

	c = 1;
	dt->red = dt->head;
	while (dt->red->next != NULL)
	{
		c++;
		dt->red = dt->red->next;
	}
	while (c > 0)
	{
		dt->red = dt->head;
		if (dt->red->next != NULL)
			dt->head = dt->red->next;
		free (dt->red->file);
		free (dt->red);
		c--;
	}
}
