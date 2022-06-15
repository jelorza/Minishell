//Tengo la primera lista terminada aunque me falta corregir que si la primera en el prompt es | me haga algo igual al bash. Lo libero todo y todo perfect. Todo esta con entructura de listas. Ahora vou a hacer otra lista con cada nodo de la lista de los comandos pero teniendo en cuenta las redirecciones.
//Tambien tengo que controlar que cuando hay una ' o " despues de | me haga bien. (asdf|asdf|'asdf')
#include "minishell.h"

void	ft_struct_init(t_struct *structInit)
{
	t_pipes *l_parseInit = NULL;
	t_redir *l_parseRedir = NULL;
	t_cmd *l_parseCmd = NULL;
	t_rest *l_parseRest = NULL;
	structInit->l_parseInit = l_parseInit;
	structInit->l_parseRedir = l_parseRedir;
	structInit->l_parseCmd = l_parseCmd;
	structInit->l_parseRest = l_parseRest;
}

void	ft_cleanAllLists(t_struct *structInit)
{	
	ft_cleanListPipe(&structInit->l_parseInit);
	ft_cleanListCmd(&structInit->l_parseCmd);
	ft_cleanListRedir(&structInit->l_parseRedir);
	ft_cleanListRest(&structInit->l_parseRest);
}

int main(int argc, char **argv, char **envp)
{
	char	*line;	
	t_in	dt;
	t_struct structInit;

	line = "Enter";
	if (argc != 1 || ft_compare_str(*argv, "./minishell") != 1)
	{
		printf ("Error in arguments\n");
		return (0);
	}
	ft_struct_init(&structInit);
	ft_get_env(&dt, envp);
	while(!ft_compare_str(line, "exit"))
	{
		if (!ft_compare_str(line,"Enter"))
			free(line); 
		line = readline(ROJO_T "minish> " RESET_C);//texto de entrada de bash
		ft_parse_line(line, &structInit, &dt);
		ft_cleanAllLists(&structInit);
	}
//	ft_printList(&structInit.l_parseInit);
//	ft_free_1(&dt);
	//system ("leaks minishell");
	return (0);
}
