//Tengo la primera lista terminada aunque me falta corregir que si la primera en el prompt es | me haga algo igual al bash. Lo libero todo y todo perfect. Todo esta con entructura de listas. Ahora vou a hacer otra lista con cada nodo de la lista de los comandos pero teniendo en cuenta las redirecciones.
//Tambien tengo que controlar que cuando hay una ' o " despues de | me haga bien. (asdf|asdf|'asdf')
#include "minishell.h"

void	ft_struct_init(t_in *dt)
{
	dt->l_parseInit = NULL;
	dt->l_parseRedir = NULL;
	dt->l_parseCmd = NULL;
	dt->hd = NULL;
	dt->env = NULL;
	dt->env_name = NULL;
	dt->env_value = NULL;
	dt->root = NULL;
	dt->rootold = NULL;
	dt->status = -1;//inicio el valor de retorno
}

void	ft_cleanAllLists(t_in *dt)
{
	dt->l_parseInit = dt->hdI;
	dt->l_parseCmd = dt->hdC;
	ft_cleanListPipe(&dt->l_parseInit);
	ft_cleanListCmd(&dt->l_parseCmd);
//	printf ("<%s>\n", dt->hdR->data);
//	dt->l_parseRedir = dt->hdR;
//	printf ("<%s>\n", dt->l_parseRedir->data);
/*	if (dt->l_parseRedir)
	{	
		dt->l_parseRedir = dt->hdR;
	}
*/	ft_cleanListRedir(&dt->l_parseRedir);
}

int main(int argc, char **argv, char **envp)
{
	char	*line;	
	t_in	dt;

	line = NULL;
	if (argc != 1 || ft_compare_str(*argv, "./minishell") != 1)
	{
		printf ("Error in arguments\n");
		return (0);
	}
	ft_struct_init(&dt);
	ft_get_env(&dt, envp);//me guardo el env y la ruta inicial
	while(1)
	{
		line = readline(ROJO_T "bash-3.2$ " RESET_C);//texto de entrada de bash
		add_history (line);//añadido el history al minishell
		if (!line || ft_compare_str(line, "E") == 1)
			break; 
		if (ft_parse_line(line, &dt) == -1)//inicio el programa
		{
			ft_cleanAllLists(&dt);
			break;
		}
		free (line);
		ft_cleanAllLists(&dt);
	}
	ft_free_1(&dt);//libero el enviroment
	ft_free_0(&dt);
//	ft_cleanAllLists(&dt);
	free (line);
	system ("leaks minishell");
	return (dt.status);
}
