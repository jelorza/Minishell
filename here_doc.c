#include "minishell.h"

//función que chequea la lista de redirecciones y mira si hay o no algun <<.
//1- Retorna 0 si no hay ninguno
//2- Retorna -1 si algo da error
//3- Retorna -2 si hay alguno pero no es predominante
//4- Retorna -3 si el último es predominante y hay alguno no predominante
//5- Retorna -4 si solo hay uno y es predominante
int	ft_ch_HD(t_in *dt, int n)
{
	t_list	*new;

	printf ("Tipo predominante de entrada: %d\n", dt->tint);
	dt->hd = NULL;
	dt->red = dt->head;
	while (dt->red)
	{
		if (dt->red->t == 3 && dt->tint == 1)//añado el nuevo nodo que es no predominante
		{
			new = ft_new(dt->red->file, n, 1);
			ft_add_back(&dt->hd, new);
		}
		else if (dt->red->t == 3 && dt->tint == 3)//añado el nuevo nodo que es predominante
		{
			new = ft_new(dt->red->file, n, 2);
			ft_add_back(&dt->hd, new);
		}
		dt->red = dt->red->next;
	}
	if (dt->hd)
	{
		printf ("Entro\n");
		dt->headh = dt->hd;
	}
	ft_print_list(dt->hd);
	return (0);
}

//función que activa uno o varios HD y los va cerrando consecutivamente sin tener que guardar la información
void	ft_exe_null_HD(char *str)
{
	char *line;

	line = readline("> ");
	while (ft_compare_str(line, str) != 1)
	{
		free (line);
		line = readline("> ");
	}
	free(line);
}
		

