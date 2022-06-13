#include "minishell.h"

//Tengo que solucionar que si despues de | si mete " o ' me lo coja bien; (asd|ads|'asdf');
//Ya tengo las estructuras hechas con varos controles. Ahora estoy queriando minimizar las funciones en partes mas pequenas y funcionales pero no puedo ya que tengo demasiadas funciones asi que tengo que hacer estructura para los datos seguramente.
//Luego ya me pongo con las cosas mas pequenas como la gestion de las comillas y hacer otra estructura para los here doc (redirect)

void	ft_parse_line(char *line, t_struct *structInit)
{
	ft_pipes_list(line,structInit); // crea la lista de pipes con la linea como dato.	
	ft_div_in_lists(structInit); //crear la lista de redirecciones
//	printf("Lista de pipe\n");
//	ft_printListPipe(&structInit->l_parseInit);
	printf("Lista de cmd\n");
	ft_printListCmd(&structInit->l_parseCmd);
	printf("Lista de redir\n");
	ft_printListRedir(&structInit->l_parseRedir);
	printf("Lista de rest\n");
	ft_printListRest(&structInit->l_parseRest);
}	

int	ft_check_and_create(char *line, t_struct *structInit, int id)
{
	int	i;
	int	z;
	char	type;
	char 	*data;

	i = 0;
	z = 0;
	while (line[i] == ' ' && line[i]) // quito los espacios en caso de que los haya
	{
		z++;
		i++;
	}
	if (line[i] == '>' || line[i] == '<')
	{
		type = ft_redir_type(line[i], line [i + 1], line [i + 2]);
		if (type == '3' || type == '4')
			i++;
		//else if (type == '5')
		//	 ;
		i++;
		while (line[i] == ' ' && line[i]) // quito los espacios en caso de que los haya
			i++;
		z = i;
		while (line[i] != ' ' && line[i]) // quito los espacios en caso de que los haya
			i++;
		data = ft_substr(line, z, i);
		ft_addNodBack(structInit, data, type, id);
		while (line[i] == ' ' && line[i])
			i++;
		z = i;
		while (line[i])
		{
			while (line[i] != ' ' && line[i])
				i++;
			while (line[i] == ' ' && line[i])
				i++;
			if (line[i] && line[i] == '-') // checo si hay un guion
			{
				while (line[i] == '-' && line[i + 1] != ' ' && line[i]) //seguimos buscando guiones.
				{
					i++;
					while (line[i] != ' ' && line[i]) // si hay testo, evanzo
						i++;
					while (line[i] == ' ' && line[i]) //si hay espacio, avanzo. Vuelvo a repetir hasta que no haya -.
						i++;
				}
				data = ft_substr(line, z, i); //ya doy por hecho que no hay mas guiones por lo que el comando termina
				ft_addNodBack(structInit, data, 'c', id);
			}
			else
			{
				data = ft_substr(line, z, i); //ya doy por hecho que no hay mas guiones por lo que el comando termina
				ft_addNodBack(structInit, data, 'c', id);
			}
			while (line[i] && line[i] == ' ') // quito los espacios en caso de que los haya
				i++;
			if (line[i] && (line[i] == '<' || line[i] == '>')) // por redireccionamineto
			{
				type = ft_redir_type(line[i], line [i + 1], line [i + 2]);
				if (type == '3' || type == '4')
					i++;
				else if (type == '5')
					break ;
				i++;
				while (line[i] == ' ' && line[i]) // quito los espacios en caso de que los haya
					i++;
				z = i;
				while (line[i] != ' ' && line[i]) // quito los espacios en caso de que los haya
					i++;
				data = ft_substr(line, z, i);
				ft_addNodBack(structInit, data, type, id);
			}
			else if (line[i])
			{
				z = i;
				while (line[i] && line[i] != ' ')
					i++;
				data = ft_substr(line, z, i); //ya doy por hecho que no hay mas guiones por lo que el comando termina
				ft_addNodBack(structInit, data, 's', id);
			}
		}
	}
	else
	{
		while (line[i] != ' ' && line[i]) // avanzo hasta quehaya un espacio
			i++;
		while (line[i] == ' ' && line[i])
			i++;
		if (line[i] && line[i] == '-') // checo si hay un guion
		{
			while (line[i] == '-' && line[i + 1] != ' ' && line[i]) //seguimos buscando guiones.
			{
				i++;
				while (line[i] != ' ' && line[i]) // si hay testo, evanzo
					i++;
				while (line[i] == ' ' && line[i]) //si hay espacio, avanzo. Vuelvo a repetir hasta que no haya -.
					i++;
			}
			data = ft_substr(line, z, i); //ya doy por hecho que no hay mas guiones por lo que el comando termina
			ft_addNodBack(structInit, data, 'c', id);
		}
		else
		{
			data = ft_substr(line, z, i); //ya doy por hecho que no hay mas guiones por lo que el comando termina
			ft_addNodBack(structInit, data, 'c', id);
		}
		while (line[i]) //Bucle que me este checando sobras y redirecciones.
		{
			while (line[i] && line[i] == ' ') // quito los espacios en caso de que los haya
				i++;
			i = ft_checkRedirect(line, i, structInit, id);
			if (i == 0)
				return (0);
	/*
			if (line[i] && (line[i] == '<' || line[i] == '>')) // por redireccionamineto
			{
				type = ft_redir_type(line[i], line [i + 1], line [i + 2]);
				if (type == '3' || type == '4')
					i++;
				else if (type == '5')
					return (0);
				i++;
				while (line[i] == ' ' && line[i]) // quito los espacios en caso de que los haya
					i++;
				z = i;
				if (line[i] == '>' || line[i] == '<')
				{
					printf("syntas error near unexpected token`%c'\n", line[i]);
					return(0);
				}
				while (line[i] != ' ' && line[i]) // quito los espacios en caso de que los haya
					i++;
				data = ft_substr(line, z, i);
				ft_addNodBack(structInit, data, type, id);
	*/
			}
			else if (line[i])
			{
				z = i;
				while (line[i] && line[i] != ' ')
					i++;
				data = ft_substr(line, z, i); //ya doy por hecho que no hay mas guiones por lo que el comando termina
				ft_addNodBack(structInit, data, 's', id);
			}
		}
	}
	return (1);
}

int	ft_checkRedirec(char * line, int i, t_struct *structInit)
{
	char *data;
	char type;

	if (line[i] && (line[i] == '<' || line[i] == '>')) // por redireccionamineto
	{
		type = ft_redir_type(line[i], line [i + 1], line [i + 2]);
		if (type == '3' || type == '4')
			i++;
		else if (type == '5')
			return (0);
		i++;
		while (line[i] == ' ' && line[i]) // quito los espacios en caso de que los haya
			i++;
		z = i;
		if (line[i] == '>' || line[i] == '<')
		{
			printf("syntas error near unexpected token`%c'\n", line[i]);
			return(0);
		}
		while (line[i] != ' ' && line[i]) // quito los espacios en caso de que los haya
			i++;
		data = ft_substr(line, z, i);
		ft_addNodBack(structInit, data, type, id);
	}
	return (i);
}

char	ft_redir_type(char type, char nType, char nnType)
{
	if ((type == '<' && nType == '<' && nnType =='<') || (type == '>' && nType == '>' && nnType == '>'))
	{
		printf("syntas error near unexpected token `%c'\n", nnType);
		return('5');
	}
	else if (type == '<' && nType == ' ')
		return ('1');
	else if (type == '>' && nType == ' ')
		return ('2');
	else if (type == '<' && nType == '<')
		return ('3');
	else if (type == '>' && nType == '>') 
		return ('4');
	else
		return (0);

}

void	ft_div_in_lists(t_struct *structInit)
{
	int ret;
	if (structInit->l_parseInit)
	{
		t_pipes *aux;
		aux = structInit->l_parseInit;
		while(aux != NULL)
		{
			ret = ft_check_and_create(aux->data, structInit, aux->id);
			aux = aux->next;
			if (ret == 0)
			{
				ft_cleanAllLists(structInit);
				break;
			}
		}
	}
}

int	ft_check_quotations(char *line, int i)
{
	if (line[i] == 39)
	{
		if (line[++i])
		{
			printf("existo\n");
			while(line[i] != 39 && line[i])
				i++;
		}
		if (!line[i])
		{
			printf("ERROR:solo abro commillas pero no las cierro por lo que me tengo que quedar colgado\n");
			exit (1);	
		}
	}
	else if (line[i] == '"')
	{
		if (line[++i])
		{
			printf("existo\n");
			while(line[i] != '"' && line[i])
				i++;
		}
		if (!line[i])
		{
			printf("ERROR:solo abro commillas pero no las cierro por lo que me tengo que quedar colgado\n");
			exit (1);	
		}
	}
	return (i);
}

void	ft_pipes_list(char *line, t_struct *structInit)
{
	int	i;
	int	z;
	char 	*data;
	
	i = 0;
	z = 0;
	while (line[i])
	{
		while(line[i] != '|' && line[i] )
		{
			i = ft_check_quotations(line, i);
			i++;
			if (line[i] == '|' && line[i + 1] == '|')
				break ;
		}
		data = ft_substr(line, z, i);
		ft_addNodBack(structInit, data, 'p',0);
		if (line[i] == '|' && line[i + 1] != '|')
			i++;
		else
		{
			while (line[i])
				i++;
		}
		z = i;
		i++;
	}
	
}
