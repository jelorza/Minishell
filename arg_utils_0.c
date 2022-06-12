#include "minishell.h"

//funcion que rompe la linea por los pipes y copia en cadenas individuales "data[i]" argumento a argumento
int	ft_break_line(char *line, t_in *dt)
{
	int		i;
	int		st;//contador de inicio de la cadena a copiar
	int		len;//contidad de chars a copiar

	i = -1;
	dt->data = (char **) malloc (sizeof (char *) * (ft_count_arg(line) + 1));
	dt->cmd = (char **) malloc (sizeof (char *) * (ft_count_arg(line) + 1));
	dt->rest = (char **) malloc (sizeof (char *) * (ft_count_arg(line) + 1));
	if (dt->data == NULL || dt->cmd == NULL || dt->rest == NULL)
		return (1);//aqui aun no hay nada que liberar
	st = 0;
	len = 0;
	while (++i < ft_count_arg(line))
	{
		if (i != 0)
			st = st + len + 1;
		len = ft_count_arg_ind(line, st);
		dt->data[i] = ft_strlcpy (line, st, len);
//		printf ("El argumento %d:\n-%s-\n", i, dt->data[i]);
	}
	dt->data[i] = NULL;
	ft_check_arg (dt);//nuevo chequeo de los datos de entrada para generar los arrays
	ft_exec(dt);//lanzo la ejecucion
	ft_free(dt, 0);//funcion que libera los argumentos
	return (0);
}

//funcion que cuenta por cada linea escrita la cantidad de argumentos separandos por pipes y los guarda en data
int	ft_count_arg(char *line)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	while (line[i] != 00)
	{
		if (line[i] == '|')
			n++;
		i++;
	}
	return (n);
}

//funcion que cuenta el largo de cada argumento emtido entre pipes teniendo como dato donde arrancar dentro de line
int	ft_count_arg_ind(char *line, int st)
{
	int	i;

	i = 0;
	while (line[st + i] != 00)
	{
		if (line[st + i] == '|')
			break;
		i++;
	}
	return (i);
}

//funcion que de nuevo chequea los datos de entrada entre pipes y busca ahora:
//1- Los cmd con sus flags 
//2- Las redirecciones, sean < o >
//3- Resto de informacion entre comillas " o '
//4- Lanza la ejecucion de los comandos
void	ft_check_arg(t_in *dt)
{
	int		i;

	i = -1;
	dt->red = NULL;//reseteo la lista de red cada redline
	while (dt->data[++i] != NULL)
	{
		ft_comf(dt->data[i], i, dt);//busco los comandos
		ft_redf(dt->data[i], i, dt);//busco las redirecciones
		ft_resf(dt->data[i], i, dt);//busco el resto
	}
	dt->cmd[i] = NULL;
	dt->rest[i] = NULL;
}

//funcion que busca el comando y lo guarda en el array cmd
void	ft_comf(char *data, int n, t_in *dt)
{
	int	i;
	int	st;
	int	len;

	i = -1;
	st = 0;
	len = 0;
	while (data[++i] != 00)
	{
		if (data[i] >= 65 && data[i] <= 122)
		{
			st = i;
			while (data[i] >= 65 && data[i] <= 122)
				i++;
			len = i - st;
			while (data[i] != 00 && data[i] != 45)
				i++;
			if (data[i] == 45)
			{
				i++;
				while (data[i] >= 97 && data[i] <= 122)
					i++;
				len = i - st;
				break;
			}
			else
				break;
		}		
	}
	dt->cmd[n] = ft_strlcpy(data, st, len);
//	printf ("El comando %d:\n<%s>\n", n, dt->cmd[n]);
}

//función que va a guardar las redirecciones en la lista red, donde recogera el nombre del archivo, el tipo de redireccion y el comando al que afecta (n)
void	ft_redf(char *data, int n, t_in *dt)
{
	int		i;
	int		t;//guardo el tipo de redireccion
	char	*file;//nombre del archivo
	t_list	*new;
	int		st;
	int		len;

	i = 0;
	st = 0;
	len = 0;
	t = 0;
	while (data[i] != 00)
	{
		file = NULL;
		if (data[i] == '<')//redirecciones de entrada
		{
			if (data[i + 1] == '<' && data[i + 1] != 00)
				t = 3;//here dock
			else 
				t = 1;//redireccion de entrada
			while ((data[i] == 60 || data[i] == 32) && data[i] != 00)
				i++;
			st = i;
			while (data[i] >= 33 && data[i] <= 126 && data[i] != 00)
				i++;
			len = i - st;
			file = ft_strlcpy(data, st, len);
		}
		else if (data[i] == '>')//redirecciones de entrada
		{
			if (data[i + 1] == '>' && data[i + 1] != 00)
				t = 4;//redireccion de salida doble
			else
				t = 2;//redireccion de salida simple
			while ((data[i] == 62 || data[i] == 32) && data[i] != 00)
				i++;
			st = i;
			while (data[i] >= 33 && data[i] <= 126 && data[i] != 00)
				i++;
			len = i - st;
			file = ft_strlcpy(data, st, len);
		}
		if (file != NULL)
		{
			new = ft_new(file, n, t);
			ft_add_back(&dt->red, new);
		}
		if (data[i] != 00)
			i++;
	}
	dt->head = ft_new(NULL, 0, 0);//hay  cabeza y hay que liberarla tambien!!!
	dt->head = dt->red;
//	ft_print_list (&dt->red);
}

//función que va a guardar el resto de informacion de data en rest. Pueden ser cosas con " o '
void	ft_resf(char *data, int n, t_in *dt)
{
	int	i;
	int	st;
	int	len;

	i = -1;
	st = 0;
	len = 0;
	while (data[++i] != 00)
	{
		if (data[i] == '\"')
		{
			i++;
			st = i;
			while ((data[i] >= 35 && data[i] <= 126) || data[i] == 33)
				i++;
			len = i - st;
			break;
		}
		else if (data[i] == '\'')
		{
			i++;
			st = i;
			while ((data[i] >= 33 && data[i] <= 38) || (data[i] == 40 && data[i] <= 126))
				i++;
			len = i - st;
			break;
		}
	}
	dt->rest[n] = ft_strlcpy(data, st, len);
//	printf ("El resto %d es:\n<%s>\n", n, dt->rest[n]);
}
