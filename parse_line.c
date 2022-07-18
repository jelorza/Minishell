#include "minishell.h"

int	ft_parse_line(char *line, t_in *dt) // Funcion principal de parseo.
{
	line = ft_expand_envs(line, dt); // Checar si entre pipes se encuentra un $. Si es asi sustituirla por la variable de entorno.
	if (ft_pipes_list(line, dt) == -1) // crea la lista de pipes con la linea como dato.
	{
		free (line);
		return (0);
	}
	ft_remove_quot(dt);
	ft_div_in_lists(dt); //crear las listas con sus respectivos datos del comando (cmds, redirect)
//	ft_printAllLists(dt); // Imprimir listas
	free (line);
	if (ft_exec(dt) == -1)
		return (-1);
	return (0);
}	

void	ft_remove_quot(t_in *dt)
{
	int i;
	char *aux;

	aux = ft_strdup(dt->l_parseInit->data);
	i = 0;
	while (aux[i])
	{
		if (aux[i] == '"' )
		{
			dt->l_parseInit->data[i] = 1;
			while (aux[++i] != '"' && aux[i])
			{
				dt->l_parseInit->data[i] = aux[i] ;
			}
			dt->l_parseInit->data[i] = 1;
		}
		else if (aux[i] == 39)
		{
			dt->l_parseInit->data[i] = 1;
			while (aux[++i] != 39 && aux[i])
			{
				dt->l_parseInit->data[i] = aux[i] ;
			}
			dt->l_parseInit->data[i] = 1;
		}
		else
		{
			dt->l_parseInit->data[i] = aux[i];
		}
		i++;
	}
	free(aux);
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
			isEnv = ft_checkInEnvList(env[0], dt); // Devuelve la posicion del array en la que esta la env
			env[1] = ft_strdup(dt->env_value[isEnv]); //Duardo el valor de la env
			env[2] = ft_replaceInLine(env[2], env[0], env[1]); //En la linea, sustituio el nombre del env por su valor
			free(env[1]);
		}
		free(env[0]);
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
				if (line[i] == c)
					count++;
				i++;
			}
		}
		i = ft_checkIf39(line, i);
		if(line[i] == c)
			count++;
	}
	return(count);
}

int	ft_checkIf39(char *line, int i)
{
	if (line[i] == 39)
	{
		i++;
		while(line[i] != 39 && line[i])
			i++;
	}
	return (i);
}

char	*ft_checkIf$(char *line, int i)
{
	char *env;
	int z;

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
}

char	*ft_checkEnv(char *line)
{
	int i;
	int z;

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
					return(ft_checkIf$(line, i));
				i++;
			}
		}
		i = ft_checkIf39(line, i);
		if (line[i] == '$')
			return (ft_checkIf$(line, i));
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

char	*ft_replaceIfEnv(char *line, int *c, char *new, char *result)
{
	int z = 0;

	while (new[z])
	{
		result[c[1]] = new[z];
		c[1]++;
		z++;
	}
	while (line[c[0]] != ' ' && line[c[0]] && line[c[0]] != '"' && line[c[0]] != 39)
		c[0]++;
	while (line[c[0]])
	{
		result[c[1]] = line[c[0]];
		c[0]++;
		c[1]++;
	}
	result[c[1]] = 00;
	return (result);
}

char	*ft_replaceInLine(char *line, char *old, char *new)
{
	int c[2]; //counters
	char *result;

	c[0] = -1; //i
	c[1] = 0; //y
	result = malloc(sizeof(char *) * (ft_strlen(line) - ft_strlen(old) + ft_strlen(new)) + 1);
	while (line[++c[0]])
	{
		if(line[c[0]] == '"')
		{
			result[c[1]] = line[c[0]];
			c[0]++;
			c[1]++;
			while(line[c[0]] != '"' && line[c[0]] )
			{
				if (line[c[0]] == '$')
				{
					result = ft_replaceIfEnv(line,c,new,result);
					free(line);
					return (result);
				}
				else
				{
					result[c[1]] = line[c[0]];
					c[0]++;
					c[1]++;
				}
			}
		}
		if (line[c[0]] == 39)
		{
			result[c[1]] = line[c[0]];
			c[1]++;
			while (line[++c[0]] != 39 && line[c[0]])
			{
				result[c[1]] = line[c[0]];
				c[1]++;
			}
		}
		if (line[c[0]] == '$')
		{
			result = ft_replaceIfEnv(line,c,new,result);
			break ;
		}
		else
		{
			result[c[1]] = line[c[0]];
			c[1]++;
		}
	}
	free(line);
	result[c[1]] = 00;
	return (result);
}

int	ft_pipes_list(char *line, t_in *dt)
{
	int	i;
	int	z;
	int	c;
	char 	*data;
	
	i = 0;
	z = 0;
	c = 0;

	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (-1);
	}
	while (i < ft_strlen(line))
	{
		while(line[i] != '|' && line[i] )
		{
			i = ft_check_quotations(line, i);
			i++;
			if (line[i] == '|' && line[i + 1] == '|')
				break ;
		}
		if (line[i] == '|' && (line[i + 1] == ' ' || line[i + 1] == '|'))
		{
			c = i;
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '|')
			{
				printf("bash: syntax error near unexpected token `|'\n");
				return(-1);
			}
			else
				i = c;
		}
		data = ft_substr(line, z, i);
		ft_addNodBack(dt, data, 'p',0);
		if (line[i] == '|' && line[i + 1] != '|')
			i++;
		else
		{
			while (line[i])
				i++;
		}
		z = i;
	}
	return (0);
}

int	ft_check_quotations(char *line, int i)
{
	if (line[i] == 39 || line[i] == 1)
	{
		if (line[++i])
		{
			while((line[i] != 39 && line[i] != 1) && line[i])
				i++;
		}
		if (!line[i])
		{
			printf("ERROR:solo abro commillas pero no las cierro por lo que me tengo que quedar colgado\n");
			exit (1);	
		}
	}
	else if (line[i] == '"' && line[i] == 1)
	{
		if (line[++i])
		{
			while((line[i] != '"' || line[i] != 1)  && line[i])
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

void	ft_div_in_lists(t_in *dt)
{
	int ret;
	if (dt->l_parseInit)
	{
		t_list *aux;
		aux = dt->l_parseInit;
		while(aux != NULL)
		{
			ret = ft_check_and_create(aux->data, dt, aux->id);
			aux = aux->next;
			if (ret == 0)
			{
				ft_cleanAllLists(dt);
				dt->l_parseInit = NULL;
				dt->hdI = NULL;
				break;
			}
		}
	}
}

int	ft_check_and_create(char *line, t_in *dt, int id)
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
			type = ft_redir_type(line, i);
			if (type == '3' || type == '4')
				i++;
			else if (type == '5')
				return (0);
			else if (type == '6') 
				break ;
			i++;
			if (line[i] == ' ')
			{
				while (line[i] == ' ' && line[i]) // quito los espacios en caso de que los haya
				i++;
			}
			z = i;
			if (line[i] == '>')
			{
				printf("syntax error near unexpected token`%c'\n", line[i]);
				return(0);
			}
			while (line[i] != ' ' && line[i]) // quito los espacios en caso de que los haya
			{
				i = ft_check_quotations(line, i);
				i++;
			}
			data = ft_substr(line, z, i);
			ft_addNodBack(dt, data, type, id);
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
			if (dt -> l_parseCmd == NULL || ft_checkAndCreate(dt, 0, data) != id)
				ft_addNodBack(dt, data, 'c', id);
			else
				ft_checkAndCreate(dt, 1, data);
		}
	}
	return (1);
}

int ft_checkAndCreate (t_in *dt, int bool, char *data)
{
	t_list	*aux;
	int ret;
	aux = dt -> l_parseCmd;
	ret = 0;
	if (aux ->next)
	{
		while (aux -> next != NULL)
			aux = aux->next;
	}
	if (bool == 1)
		aux -> data = ft_strjoinAux(aux -> data, data);
	ret = aux -> id;
	return(ret);
}


char	ft_redir_type(char *line, int i)
{
	int z;

	z = i;
	i++;
	if (line[i] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '<' || line[i] == '>')
		{
			printf("syntas error near unexpected token `%c' \n", line[i]);
			return('5');
		}
	}	
	i = z;
	if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>' && line[i + 3] == '>')
	{
		printf("syntas error near unexpected token `%c%c' \n", line[i + 2], line[i + 3]);
		return('5');
	}
	else if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
	{
		printf("syntas error near unexpected token `%c' \n", line[i + 2]);
		return('5');
	}
	else if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<' && line[i + 3] == '<' && line[i + 4] == '<' && line[i + 5] == '<')
	{
		printf("syntas error near unexpected token `%c%c%c' \n", line[i + 2], line[i + 3], line[i + 4]);
		return('5');
	}
	else if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<' && line[i + 3] == '<' && line[i + 4] == '<')
	{
		printf("syntas error near unexpected token `%c%c' \n", line[i + 2], line[i + 3]);
		return('5');
	}
	else if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<' && line[i + 3] == '<')
	{
		printf("syntas error near unexpected token `%c' \n", line[i + 2]);
		return('5');
	}
	else if (line[i] == '<' && line[i + 1] != '<')
		return ('1');
	else if (line[i] == '>' && line[i + 1] != '>')
		return ('2');
	else if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
		return ('6');
	else if (line[i] == '<' && line[i + 1] == '<')
	{
		return ('3');
	}
	else if (line[i] == '>' && line[i + 1] == '>') 
		return ('4');
	else
		return (0);
}

void	ft_printAllLists(t_in *dt)
{
	printf("Lista de pipe\n");
	ft_printListPipe(&dt->l_parseInit);
	printf("Lista de cmd\n");
	ft_printListCmd(&dt->l_parseCmd);
	printf("Lista de redir\n");
	ft_printListRedir(&dt->l_parseRedir);
}
