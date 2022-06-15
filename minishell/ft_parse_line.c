#include "minishell.h"

//Tengo que solucionar que si despues de | si mete " o ' me lo coja bien; (asd|ads|'asdf');
//Ya tengo las estructuras hechas con varos controles. Ahora estoy queriando minimizar las funciones en partes mas pequenas y funcionales pero no puedo ya que tengo demasiadas funciones asi que tengo que hacer estructura para los datos seguramente.
//He hecho algo con las commilas teniendo en cuenta el resto. Ahora puede ser que cuando pase el resto a array tenga que quitarle las comillas en caso de que las tenga. Tengo que mirar en que mas casos las comillas funcionan y si no empezar con las variables de entorno.
//He terminado con las env, tengo que mirar el caso del terinador del strdup. preguntar por el caso de '$USER      ', y tambien mirar el caso de que metan la env con ""

void	ft_parse_line(char *line, t_struct *structInit, t_in *dt)
{
	line = ft_expand_envs(line, dt); //checar si el entre pipes se encuentra un $. Si es asi sustituirla por la variable de entorno.
	ft_pipes_list(line,structInit); // crea la lista de pipes con la linea como dato.	
	ft_div_in_lists(structInit); //crear las listas on sus respectivos datos del comando (cmds, redirect, rest)
	printf("Lista de pipe\n");
	ft_printListPipe(&structInit->l_parseInit);
	printf("Lista de cmd\n");
	ft_printListCmd(&structInit->l_parseCmd);
	printf("Lista de redir\n");
	ft_printListRedir(&structInit->l_parseRedir);
	printf("Lista de rest\n");
	ft_printListRest(&structInit->l_parseRest);
	free(line);
}	

int	ft_count_$(char *line)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (line[++i])
	{
		if(line[i] == '$')
			count++;
	}
	return(count);
}

int	ft_checkInEnvList(char *env, t_in *dt)
{
	int i;

	i = 0;
	while (dt->env_name[i])
	{
		if (ft_compare_str(env,dt->env_name[i]))
			return (i);
		i++;
	}
	return (0);
}

char	*ft_replaceInLine(char *line, char *old, char *new)
{
	int i;
	int z;
	int y;
	char *result;

	y = 0;
	i = 0;
	z = 0;
	result = malloc(sizeof(char *) * (ft_strlen(line) - ft_strlen(old) + ft_strlen(new)) + 1);
	while (line[i])
	{
		if (line[i] == 39)
		{
			result[y] = line[i];
			i++;
			y++;
			while (line[i] != 39 && line[i])
			{
				result[y] = line[i];
				y++;
				i++;
			}
		}
		if (line[i] == '$')
		{
			while (new[z])
			{
				result[y] = new[z];
				y++;
				z++;
			}
			while (line[i] != ' ' && line[i])
				i++;
			while (line[i])
			{
				result[y] = line[i];
				y++;
				i++;
			}
			break ;
		}
		else
		{
			result[y] = line[i];
			i++;
			y++;
		}
	}
	line = NULL;
	free(line);
	result[y] = 00;
	return (result);
}

char	*ft_expand_envs(char *line, t_in *dt)
{
	char *env[3];
	int isEnv;
	int n;

	env[2] = ft_strdup(line);
	isEnv = 0;
	n = ft_count_$(env[2]);
	while (n > 0)
	{
		env[0] = ft_checkEnv(env[2]); // Guardo el nombre de la env en caso de que exista
		if (env[0]) //Si existe variable de entorno entra
		{
			isEnv = ft_checkInEnvList(env[0], dt); 
			if (isEnv != 0)
			{
				env[1] = ft_strdup(dt->env_value[isEnv]); //guardo el valor de la env
				env[2] = ft_replaceInLine(env[2], env[0], env[1]); //En la linea, sustituio el nombre del env por su valor
			}
			free(env[1]);
			free(env[0]);
		}
		n--;
	}
	return (env[2]);
}

char	*ft_checkEnv(char *line)
{
	int i;
	int z;
	char *env;

	i = 0;
	z = 0;
	while (line[i])
	{
		if (line[i] == 39)
		{
			i++;
			while (line[i] != 39)
				i++;
		}
		if (line[i] == '$')
		{
			i++;
			z = i;
			while( line[i] != ' ' && line[i])
			{
				i++;
			}
			if (line[i - 1] == '"')
				i--;
			env = ft_substr(line,z,i);
			return (env);
			break ;
		}
		else
			i++;
	}
	return (NULL);
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
	if (line[i] && (line[i] == '<' || line[i] == '>')) // por redireccionamineto
	{
		while (line[i])
		{
			if (line[i] && (line[i] == '<' || line[i] == '>')) //primero miro los rediccionamientos en caso de que esistan
			{
				type = ft_redir_type(line[i], line [i + 1], line [i + 2]);
				if (type == '3' || type == '4')
					i++;
				else if (type == '5')
					return (0);
				i++;
				if (line[i] == ' ')
				{
					while (line[i] == ' ' && line[i])
						i++;
				}
				z = i;
				if (line[i] == '>' || line[i] == '<')
				{
					printf("syntas error near unexpected token`%c'\n", line[i]);
					return(0);
				}
				i = ft_check_quotations(line, i);
				while (line[i] != ' ' && line[i]) // quito los espacios en caso de que los haya
				i++;
				data = ft_substr(line, z, i);
				ft_addNodBack(structInit, data, type, id);
				while (line[i] != ' ' && line[i])
					i++;
				z = i;
				while (line[i] == ' ' && line[i])
					i++;
			}
			else //si no hay mas redict, rompo el bucle para que siga con los demas tipos de datos
				break ;
		}
		if (line[i])
		{
			i = ft_check_quotations(line, i);
			while (line[i] != ' ' && line[i]) // despues ira el comando si o si.
				i++;
			if (line[i] && line[i] == '-') // checo si hay un guion para implementar los flags
			{
				while (line[i] == '-' && line[i + 1] != ' ' && line[i]) //seguimos buscando guiones por si los flags vienen separados
				{
					i++;
					while (line[i] != ' ' && line[i]) 
						i++;
					while (line[i] == ' ' && line[i])
						i++;
				}
				data = ft_substr(line, z, i); 
				ft_addNodBack(structInit, data, 'c', id);
			}
			else // si no hay guiones, guardo el comando sin flags en la lista
			{
				data = ft_substr(line, z, i); //ya doy por hecho que no hay mas guiones por lo que el comando termina
				ft_addNodBack(structInit, data, 'c', id);
			}
			while (line[i] && line[i] == ' ') // quito los espacios en caso de que los haya
				i++;
			while (line[i]) // a partir de ahora lo que vengan seran o redirects o resto. Creo un bucle hasta que termine la linea y me gestione los datos.
			{
				while (line[i] && line[i] == ' ') // quito los espacios en caso de que los haya
					i++;
				if (line[i] && (line[i] == '<' || line[i] == '>')) // por redireccionamineto
				{
					type = ft_redir_type(line[i], line [i + 1], line [i + 2]);
					if (type == '3' || type == '4')
						i++;
					else if (type == '5')
						return (0);
					i++;
					if (line[i] == ' ')
					{
						while (line[i] == ' ' && line[i])
							i++;
					}
					z = i;
					i = ft_check_quotations(line, i);
					if (line[i] == '"' || line[i] == 39)
						i++;
					if (line[i] == '>' || line[i] == '<')
					{
						printf("syntas error near unexpected token`%c'\n", line[i]);
						return(0);
					}
					while (line[i] != ' ' && line[i])
						i++;
					data = ft_substr(line, z, i);
					ft_addNodBack(structInit, data, type, id);
				}
				else if (line[i])
				{
					i = ft_check_quotations(line, i);
					if (line[i] == '"' || line[i] == 39)
						i++;
					z = i;
					while (line[i] && line[i] != ' ')
						i++;
					data = ft_substr(line, z, i); //ya doy por hecho que no hay mas guiones por lo que el comando termina
					ft_addNodBack(structInit, data, 's', id);
				}
			}
		}
	}
	else // Esto el lo mismo que lo anterior pero en caso de que la linea no empieze por redirect sino por cmd.
	{
		i = ft_check_quotations(line, i);
		while (line[i] != ' ' && line[i]) 
			i++;
		while (line[i] == ' ' && line[i])
			i++;
		if (line[i] && line[i] == '-') 
		{
			while (line[i] == '-' && line[i + 1] != ' ' && line[i])
			{
				i++;
				while (line[i] != ' ' && line[i]) 
					i++;
				while (line[i] == ' ' && line[i])
					i++;
			}
			data = ft_substr(line, z, i);
			ft_addNodBack(structInit, data, 'c', id);
		}
		else
		{
			data = ft_substr(line, z, i);
			ft_addNodBack(structInit, data, 'c', id);
		}
		while (line[i])
		{
			while (line[i] && line[i] == ' ')
				i++;
			z = i;
			i = ft_check_quotations(line, i);
//			i = ft_checkRedirect(line, i, structInit, id); //esto lo tengo para que cuando empiece a dividir en funciones tenga que crear otra estructura.
	//		if (i == 0)
	//			return (0);
//	/*
			if (line[i] && (line[i] == '<' || line[i] == '>')) // por redireccionamineto
			{
				type = ft_redir_type(line[i], line [i + 1], line [i + 2]);
				if (type == '3' || type == '4')
					i++;
				else if (type == '5')
					return (0);
				i++;
				if (line[i] == ' ')
				{
					while (line[i] == ' ' && line[i]) // quito los espacios en caso de que los haya
					i++;
				}
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
//	*/
			}
			else if (line[i])
			{
				if (line[i] != '"' && line[i] != 39)
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

char	ft_redir_type(char type, char nType, char nnType)
{
	if ((type == '<' && nType == '<' && nnType =='<') || (type == '>' && nType == '>' && nnType == '>'))
	{
		printf("syntas error near unexpected token `%c'\n", nnType);
		return('5');
	}
	else if (type == '<' && nType != '<')
		return ('1');
	else if (type == '>' && nType != '>')
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
	while (i < ft_strlen(line))
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
