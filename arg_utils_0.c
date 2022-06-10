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
	dt->red = (char **) malloc (sizeof (char *) * (ft_count_arg(line) + 1));
	dt->redt = (int *) malloc (sizeof (int) * (ft_count_arg(line) + 1));
	dt->rest = (char **) malloc (sizeof (char *) * (ft_count_arg(line) + 1));
	if (dt->data == NULL || dt->cmd == NULL || dt->red == NULL || dt->rest == NULL || dt->redt == NULL)
		return (1);//aqui aun no hay nada que liberar
	st = 0;
	len = 0;
	while (++i < ft_count_arg(line))
	{
		if (i != 0)
			st = st + len + 1;
		len = ft_count_arg_ind(line, st);
		dt->data[i] = ft_strlcpy (line, st, len);
		dt->redt[i] = 0;//pongo a 0 todos los tipos de redirecciones
//		printf ("El argumento %d:\n-%s-\n", i, dt->data[i]);
	}
	dt->data[i] = NULL;
	ft_check_arg (dt);//nuevo chequeo de los datos de entrada para generar los arrays
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
	int	i;

	i = -1;
	while (dt->data[++i] != NULL)
	{
		ft_comf(dt->data[i], i, dt);//busco los comandos
		ft_redf(dt->data[i], i, dt);//busco las redirecciones
		ft_resf(dt->data[i], i, dt);//busco el resto
	}
	dt->cmd[i] = NULL;
	dt->red[i] = NULL;
	dt->rest[i] = NULL;
	ft_exec(dt);
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

//función que va a guardar las redirecciones en el array red y su tipo en el array redt (< es 1 y > es 2)
void	ft_redf(char *data, int n, t_in *dt)
{
	int	i;
	int	st;
	int	len;

	i = -1;
	st = 0;
	len = 0;
	while (data[++i] != 00)
	{
		if (data[i] == '<')
		{
			dt->redt[n] = 1;//tipo de redireccion
			while (data[i] == 60 || data[i] == 32)
				i++;
			st = i;
			while (data[i] >= 33 && data[i] <= 126)
				i++;
			len = i - st;
			break;
		}
		if (data[i] == '>')
		{
			dt->redt[n] = 2;//tipo de redireccion
			while (data[i] == 62 || data[i] == 32)
				i++;
			st = i;
			while (data[i] >= 33 && data[i] <= 126)
				i++;
			len = i - st;
			break;
		}
	}
	dt->red[n] = ft_strlcpy(data, st, len);
//	printf ("La redireccion %d es del tipo %d:\n<%s>\n", n, dt->redt[n], dt->red[n]);
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
