/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/26 17:50:17 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_line(char *line, t_in *dt)
{
	line = ft_expand_envs(line, dt);
	if (ft_pipes_list(line, dt) == -1)
	{
		free (line);
		return (0);
	}
	ft_remove_quot(dt);
	ft_div_in_lists(dt);
	//ft_printAllLists(dt);
	free (line);
	if (ft_exec(dt) == -1)
		return (-1);
	return (0);
}	

int	ft_put_noimp(t_in *dt, int i)
{
	t_list	*aux;

	aux = dt->l_parse_init;
	while (aux->data[i])
	{
		if (aux->data[i] == '"' )
		{
			dt->l_parse_init->data[i] = '!';
			while (aux->data[++i] != '"' && aux->data[i])
				dt->l_parse_init->data[i] = aux->data[i];
			dt->l_parse_init->data[i] = '!';
		}
		else if (aux->data[i] == 39)
		{
			dt->l_parse_init->data[i] = '!';
			while (aux->data[++i] != 39 && aux->data[i])
				dt->l_parse_init->data[i] = aux->data[i];
			dt->l_parse_init->data[i] = '!';
		}
		else
			dt->l_parse_init->data[i] = aux->data[i];
		i++;
	}
	return (0);
}

void	ft_remove_quot(t_in *dt)
{
	int		i;
	t_list	*aux;
	t_list	*aux2;

	aux = dt->l_parse_init;
	aux2 = dt->l_parse_init;
	while (aux)
	{
		i = 0;
		i = ft_put_noimp(dt, i);
		aux = aux->next;
		dt->l_parse_init = dt->l_parse_init->next;
		i = 0;
	}
	dt->l_parse_init = aux2;
}

void	ft_cmp_replace(char *env[3], t_in *dt, int is_env)
{
	char	*st;

	if (!ft_compare_str(env[0], "?"))
	{
		is_env = ft_check_in_env_list(env[0], dt);
		env[1] = ft_strdup(dt->env_value[is_env]);
		env[2] = ft_replace_in_line(env[2], env[0], env[1]);
		free(env[1]);
	}
	else
	{
		st = ft_itoa(g_status);
		env[2] = ft_replace_in_line(env[2], env[0], st);
		free(st);
	}
}

char	*ft_expand_envs(char *line, t_in *dt)
{
	char	*env[3];
	int		is_env;
	int		n;

	env[2] = ft_strdup(line);
	is_env = 0;
	n = ft_char_counter(line, '$');
	while (n > 0)
	{
		env[0] = ft_check_env(env[2]);
		if (ft_check_in_env_list(env[0], dt) || ft_compare_str(env[0], "?"))
			ft_cmp_replace(env, dt, is_env);
		else
			env[2] = ft_replace_in_line(env[2], env[0], " ");
		free(env[0]);
		n--;
	}
	return (env[2]);
}

int	ft_char_counter(char *line, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (line[++i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] != '"' && line[i])
			{	
				if (line[i] == c && line[i + 1] && line[i + 1] != '"' && line[i + 1] != 39)
					count++;
				i++;
			}
			printf("line[i] = %c\n", line[i]);
		}
		i = ft_check_if39(line, i);
		if (line[i] == c && line[i + 1] && line[i + 1] != '"' && line[i + 1] != 39)
			count++;
	}
	printf("count = %d\n", count);
	return (count);
}

int	ft_check_if39(char *line, int i)
{
	if (line[i] == 39)
	{
		i++;
		while (line[i] != 39 && line[i])
			i++;
	}
	return (i);
}

char	*ft_check_if_env(char *line, int i)
{
	char	*env;
	int		z;

	i++;
	z = i;
	while (line[i] != ' ' && line[i] != '$' && line[i] && line[i] != 39
		&& line[i] != '"')
		i++;
	if (line[i - 1] == '"' || line[i - 1] == 39)
	{
		if (line[i - 2] == 39)
			i--;
		i--;
	}
	env = ft_substr(line, z, i);
	return (env);
}

char	*ft_check_env(char *line)
{
	int	i;
	int	z;

	i = -1;
	z = 0;
	while (line[++i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] != '"' && line[i])
			{	
				if (line[i] == '$')
					return (ft_check_if_env(line, i));
				i++;
			}
		}
		i = ft_check_if39(line, i);
		if (line[i] == '$')
			return (ft_check_if_env(line, i));
	}
	return (NULL);
}

int	ft_check_in_env_list(char *env, t_in *dt)
{
	int	i;

	i = -1;
	while (dt->env_name[++i])
	{
		if (ft_compare_str(env, dt->env_name[i]))
			return (i);
	}
	return (0);
}

char	*ft_replace_if_env(char *line, int *c, char *new, char *result)
{
	int	z;

	z = 0;
	while (new[z])
	{
		result[c[1]] = new[z];
		c[1]++;
		z++;
	}
	while (line[c[0]] != ' ' && line[c[0]] && line[c[0]] != '"'
		&& line[c[0]] != 39)
	{
		c[0]++;
		if (line[c[0]] == '$')
			break ;
	}
	while (line[c[0]])
	{
		result[c[1]] = line[c[0]];
		c[0]++;
		c[1]++;
	}
	result[c[1]] = 00;
	return (result);
}

char	*ft_replace_in_line(char *line, char *old, char *new)
{
	int		c[2];
	char	*result;

	c[0] = -1;
	c[1] = 0;
	result = malloc(sizeof(char *) * (ft_strlen(line) - ft_strlen(old)
				+ ft_strlen(new)) + 1);
	while (line[++c[0]])
	{
		if (line[c[0]] == '"')
		{
			result[c[1]] = line[c[0]];
			c[0]++;
			c[1]++;
			while (line[c[0]] != '"' && line[c[0]])
			{
				if (line[c[0]] == '$')
				{
					result = ft_replace_if_env(line, c, new, result);
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
			result = ft_replace_if_env(line, c, new, result);
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

int	ft_create_new(char *line, int z, int i, t_in *dt)
{
	char	*data;

	data = ft_substr(line, z, i);
	ft_add_nod_back(dt, data, 'p', 0);
	if (line[i] == '|' && line[i + 1] != '|')
		i++;
	else
	{
		while (line[i])
			i++;
	}
	return (i);
}

int	ft_init(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (i);
}

int	ft_check_pipe(char *line, int i)
{
	int	c;

	c = i;
	i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (-1);
	}
	else
		i = c;
	return (i);
}

int	ft_pipes_list(char *line, t_in *dt)
{
	int		i;
	int		z;

	i = 0;
	z = 0;
	i = ft_init(line, i);
	if (i == -1)
		return (0);
	while (i < ft_strlen(line))
	{
		while (line[i] != '|' && line[i])
		{
			i = ft_check_quotations(line, i);
			if (i == -1)
				return (-1);
			i++;
			if (line[i] == '|' && line[i + 1] == '|')
				break ;
		}
		if (line[i] == '|' && (line[i + 1] == ' ' || line[i + 1] == '|'))
			i = ft_check_pipe(line, i);
		i = ft_create_new(line, z, i, dt);
		z = i;
	}
	return (0);
}

/*
int ft_check_quot(char *line, int i, char type)
{
	if (type == '1')
		type = '"';
	else
		type = 39;

	if (line[++i])
	{
		while ((line[i] != type && line[i] != '!') && line[i])
			i++;
	}
	if (!line[i])
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	return (i);
}
*/
int	ft_check_quotations(char *line, int i)
{

	if (line[i] == 39 || line[i] == '!')
	{
//		i = ft_check_quot(line, i, '1');
		if (line[++i])
		{
			while ((line[i] != 39 && line[i] != '!') && line[i])
				i++;
		}
		if (!line[i])
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (-1);
		}
//		if (i == -1)
//			return (-1);
		
	}
	else if (line[i] == '"' || line[i] == '!')
	{
	//	i = ft_check_quot(line, i, '2');
//		if (i == -1)
//			return (-1);
		if (line[++i])
		{
			while ((line[i] != '"' && line[i] != '!') && line[i])
				i++;
		}
		if (!line[i])
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (-1);
		}
	}
	return (i);
}

void	ft_div_in_lists(t_in *dt)
{
	int		ret;
	t_list	*aux;

	if (dt->l_parse_init)
	{
		aux = dt->l_parse_init;
		while (aux != NULL)
		{
			ret = ft_check_and_create(aux->data, dt, aux->id);
			aux = aux->next;
			if (ret == 0)
			{
				ft_clean_all_lists(dt);
				break ;
			}
		}
	}
}

int	ft_check_and_create(char *line, t_in *dt, int id)
{
	int		i;
	int		z;
	char	type;
	char	*data;

	i = 0;
	z = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ' && ft_count_rarus(line, i) == 0)
			i++;
		z = i;
		if (line[i] && (line[i] == '<' || line[i] == '>'))
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
				while (line[i] == ' ' && line[i])
				i++;
			}
			z = i;
			if (line[i] == '>')
			{
				printf("syntax error near unexpected token`%c'\n", line[i]);
				return (0);
			}
			while (line[i] != ' ' && line[i])
			{
				i = ft_check_quotations(line, i);
				if (i == -1)
					return (0);
				i++;
			}
			data = ft_substr(line, z, i);
			ft_add_nod_back(dt, data, type, id);
		}
		else if (line[i] && line[i] != '<' && line[i] != '>')
		{
			while (line[i] != '>' && line[i] != '<'
				&& line[i] && line[i] != ' ')
			{
				i = ft_check_quotations(line, i);
				if (i == -1)
					return (0);
				i++;
			}
			if (line[i])
				i++;
			data = ft_substr(line, z, i);
			if (dt -> l_parse_cmd == NULL
				|| ft_check_create(dt, 0, data) != id)
				ft_add_nod_back(dt, data, 'c', id);
			else
				ft_check_create(dt, 1, data);
		}
	}
	return (1);
}

int	ft_check_create(t_in *dt, int bool, char *data)
{
	t_list	*aux;
	int		ret;

	aux = dt -> l_parse_cmd;
	ret = 0;
	if (aux ->next)
	{
		while (aux -> next != NULL)
			aux = aux->next;
	}
	if (bool == 1)
		aux -> data = ft_strjoin_aux(aux -> data, data);
	ret = aux -> id;
	return (ret);
}

char	ft_redir_type(char *line, int i)
{
	int	z;

	z = i;
	if (line[i] == '<' && line[i + 1] == '>')
	{
		printf("syntax error near unexpected token `%c' \n", line[i]);
		return ('5');
	}
	else if (line[i] == '>' && line[i + 1] == '<')
	{
		printf("syntax error near unexpected token `%c' \n", line[i]);
		return ('5');
	}
	i++;
	if (line[i] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '<' || line[i] == '>')
		{
			printf("syntax error near unexpected token `%c' \n", line[i]);
			return ('5');
		}
	}
	i = z;
	if (line[i] == '>' && line[i + 1] == '>'
		&& line[i + 2] == '>' && line[i + 3] == '>')
	{
		printf("syntax error near unexpected token `%c%c' \n",
			line[i + 2], line[i + 3]);
		return ('5');
	}
	else if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
	{
		printf("syntax error near unexpected token `%c' \n", line[i + 2]);
		return ('5');
	}
	else if (line[i] == '<' && line[i + 1] == '<'
		&& line[i + 2] == '<' && line[i + 3] == '<'
		&& line[i + 4] == '<' && line[i + 5] == '<')
	{
		printf("syntax error near unexpected token `%c%c%c' \n",
			line[i + 2], line[i + 3], line[i + 4]);
		return ('5');
	}
	else if (line[i] == '<' && line[i + 1] == '<'
		&& line[i + 2] == '<' && line[i + 3] == '<' && line[i + 4] == '<')
	{
		printf("syntax error near unexpected token `%c%c' \n",
			line[i + 2], line[i + 3]);
		return ('5');
	}
	else if (line[i] == '<' && line[i + 1] == '<'
		&& line[i + 2] == '<' && line[i + 3] == '<')
	{
		printf("syntax error near unexpected token `%c' \n", line[i + 2]);
		return ('5');
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

void	ft_print_all_lists(t_in *dt)
{
	printf("Lista de pipe\n");
	ft_print_list_pipe(&dt->l_parse_init);
	printf("Lista de cmd\n");
	ft_print_list_cmd(&dt->l_parse_cmd);
	printf("Lista de redir\n");
	ft_print_list_redir(&dt->l_parse_redir);
}
