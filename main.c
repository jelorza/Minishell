//Tengo la primera lista terminada aunque me falta corregir que si la primera en el prompt es | me haga algo igual al bash. Lo libero todo y todo perfect. Todo esta con entructura de listas. Ahora vou a hacer otra lista con cada nodo de la lista de los comandos pero teniendo en cuenta las redirecciones.
//Tambien tengo que controlar que cuando hay una ' o " despues de | me haga bien. (asdf|asdf|'asdf')
#include "minishell.h"

void	ft_struct_init(t_in *dt)
{
	STATUS = 0;
	dt->l_parseInit = NULL;
	dt->hdI = NULL;
	dt->l_parseRedir = NULL;
	dt->hdR = NULL;
	dt->l_parseCmd = NULL;
	dt->hdC = NULL;
	dt->hd = NULL;
	dt->hdH = NULL;
	dt->env = NULL;
	dt->env_name = NULL;
	dt->env_value = NULL;
	dt->root = NULL;
	dt->rootold = NULL;
}

void	ft_cleanAllLists(t_in *dt)
{
	if (dt->hdI)
	{
		dt->l_parseInit = dt->hdI;
		dt->hdI = NULL;
	}
	ft_cleanListPipe(&dt->l_parseInit);
	if (dt->hdC)
	{
		dt->l_parseCmd = dt->hdC;
		dt->hdI = NULL;
	}
	ft_cleanListCmd(&dt->l_parseCmd);
	if (dt->hdR)
	{
		dt->l_parseRedir = dt->hdR;
		dt->hdI = NULL;
	}
	ft_cleanListRedir(&dt->l_parseRedir);
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
//		line = readline("bash del jonpol$ ");//texto de entrada de bash
		add_history (line);//añadido el history al minishell
		if (!line || ft_compare_str(line, "E") == 1)
			break; 
		if (ft_parse_line(line, &dt) == -1)//inicio el programa
		{
//			ft_cleanAllLists(&dt);
			break;
		}
		free (line);
		ft_cleanAllLists(&dt);
		printf ("El status que sale es: %d\n", STATUS);
	}
	ft_free_1(&dt);//libero el enviroment
	ft_free_0(&dt);
	ft_cleanAllLists(&dt);
	free (line);
//	system ("leaks minishell");
	return (STATUS);
}
