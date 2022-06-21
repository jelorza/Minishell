#include "minishell.h"

//Unir toos los comandos en 1

void	ft_parse_line(char *line, t_struct *structInit, t_in *dt) // Funcion principal de parseo.
{
	line = ft_expand_envs(line, dt); // Checar si entre pipes se encuentra un $. Si es asi sustituirla por la variable de entorno.
	ft_pipes_list(line,structInit); // crea la lista de pipes con la linea como dato.	
	ft_div_in_lists(structInit); //crear las listas con sus respectivos datos del comando (cmds, redirect, rest)
//	ft_joinCmds(structInit);
	ft_printAllLists(structInit); // Imprimir listas
	free(line);
}	

void	ft_joinCmds(t_struct *structInit)
{
	t_cmd *aux;
	char *joined;
	aux = structInit -> l_parseCmd;
	joined = malloc(1);
	while(aux)
	{
		if (aux -> id == 0)
		{
			printf("entraaa??\n");
			printf("nodos de 1 son ->) %s y pertenece a %d\n", aux->data, aux ->id);
//			joined = ft_strjoin("df", aux -> data) ;
			aux = aux -> next;
		}
		else if (aux -> id == 1)
		{
			printf("nodos de 1 son ->) %s y pertenece a %d\n", aux->data, aux ->id);
			aux = aux -> next;
		}	
		else 
			aux = aux -> next;

	}
}

char	*ft_expand_envs(char *line, t_in *dt)
{
	char *env[3];
	int isEnv;
	int n;

	env[2] = ft_strdup(line);
	isEnv = 0;
	n = ft_charCounter(line, '$');
	while (n > 0)
	{
		env[0] = ft_checkEnv(env[2]); // Guardo el nombre de la env en caso de que exista
		if (ft_checkInEnvList(env[0],dt)) //Si existe variable de entorno entra
		{
			isEnv = ft_checkInEnvList(env[0], dt);
			env[1] = ft_strdup(dt->env_value[isEnv]); //guardo el valor de la env
			env[2] = ft_replaceInLine(env[2], env[0], env[1]); //En la linea, sustituio el nombre del env por su valor
			free(env[1]);
			free(env[0]);
		}
		n--;
	}
	return (env[2]);
}

int	ft_charCounter(char *line, char c)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (line[++i])
	{
		if (line[i] == '"')
		{
			i++;
			while(line[i] != '"' && line[i] )
			{	
				if (line[i] == '$')
					count++;
				i++;
			}
		}
		if (line[i] == 39)
		{
			i++;
			while(line[i] != 39 && line[i])
				i++;
		}
		if(line[i] == c)
			count++;
	}
	return(count);
}

char	*ft_checkEnv(char *line)
{
	int i;
	int z;
	char *env;

	i = -1;
	z = 0;
	while (line[++i])
	{
		if (line[i] == '"')
		{
			i++; 
			while(line[i] != '"' && line[i])
			{	
				if (line[i] == '$')
				{	
					i++;
					z = i;
					while( line[i] != ' ' && line[i] && line[i] != 39 && line[i] != '"')
						i++;
					if (line[i - 1] == '"' || line[i - 1] == 39)
					{
						if (line[i - 2] == 39)
							i--;
						i--;
					}
					env = ft_substr(line,z,i);
					return (env);
					break ;
				}
				i++;
			}
		}
		if (line[i] == 39)
		{
			i++;
			while(line[i] != 39 && line[i])
				i++;
		}
		if (line[i] == '$')
		{
			i++;
			z = i;
			while( line[i] != ' ' && line[i] && line[i] != '"' && line[i] != 39)
				i++;
			if (line[i - 1] == '"' || line[i - 1] == 39) 
				i--;
			env = ft_substr(line,z,i);
			return (env);
			break ;
		}
	}
	return (NULL);
}

int	ft_checkInEnvList(char *env, t_in *dt) 
{
	int i;

	i = -1;
	while (dt->env_name[++i])
	{
		if (ft_compare_str(env,dt->env_name[i]))
			return (i);
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
	i = -1;
	z = 0;
	result = malloc(sizeof(char *) * (ft_strlen(line) - ft_strlen(old) + ft_strlen(new)) + 1);
	while (line[++i])
	{
		if(line[i] == '"')
		{
			result[y] = line[i];
			y++;
			i++;
			while(line[i] != '"' && line[i] )
			{
				if (line[i] == '$')
				{
					while (new[z])
					{
						result[y] = new[z];
						y++;
						z++;
					}
					while (line[i] != ' ' && line[i] && line[i] != '"' && line[i] != 39)
						i++;
					while (line[i])
					{
						result[y] = line[i];
						y++;
						i++;
					}
					result[y] = 00;
					return (result);
					exit(0);
				}
				else
				{
					result[y] = line[i];
					y++;
					i++;
				}
			}
		}
		if (line[i] == 39)
		{
			result[y] = line[i];
			y++;
			while (line[++i] != 39 && line[i])
			{
				result[y] = line[i];
				y++;
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
			while (line[i] != ' ' && line[i] && line[i] != '"' && line[i] != 39)
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
			y++;
		}
	}
	free(line);
	result[y] = 00;
	return (result);
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

int	ft_check_and_create(char *line, t_struct *structInit, int id)
{
	int	i;
	int	z;
	char	type;
	char 	*data;

	i = 0;
	z = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		z = i;
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
			{
				i = ft_check_quotations(line, i);
				i++;
			}
			data = ft_substr(line, z, i);
			ft_addNodBack(structInit, data, type, id);
		}
		else if (line[i] && line[i] != '<' && line[i] != '>')
		{
			while (line[i] != '>' && line[i] != '<' && line[i] && line[i] != ' ')
			{
				i = ft_check_quotations(line, i);
				i++;
			}
			if (line[i])
				i++;
			data = ft_substr(line, z, i);
			if (structInit -> l_parseCmd == NULL || ft_checkAndCreate(structInit, 0, data) != id)
				ft_addNodBack(structInit, data, 'c', id);
			else
				ft_checkAndCreate(structInit, 1, data);
		}
	}
	return (1);
}

int ft_checkAndCreate (t_struct *structInit, int bool, char *data)
{
	t_cmd	*aux;
	int ret;
	aux = structInit -> l_parseCmd;
	ret = 0;
	if (aux ->next)
	{
		while (aux -> next != NULL)
			aux = aux->next;
	}
	if (bool == 1)
		aux -> data = ft_strjoin(aux -> data, data);
	ret = aux -> id;
	return(ret);
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

void	ft_printAllLists(t_struct *structInit)
{
	printf("Lista de pipe\n");
	ft_printListPipe(&structInit->l_parseInit);
	printf("Lista de cmd\n");
	ft_printListCmd(&structInit->l_parseCmd);
	printf("Lista de redir\n");
	ft_printListRedir(&structInit->l_parseRedir);
//	printf("Lista de rest\n");
//	ft_printListRest(&structInit->l_parseRest);
}
