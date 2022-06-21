#include "minishell.h"

//funcion que rompe la linea por los pipes y copia en cadenas individuales "data[i]" argumento a argumento
int	ft_break_line(char *line, t_in *dt)
{
	int		i;
	int		st;//contador de inicio de la cadena a copiar
	int		len;//contidad de chars a copiar

	i = -1;
	dt->data = (char **) malloc (sizeof (char *) * (ft_count_arg(line) + 1));
	if (dt->data == NULL)
		return (1);//aqui aun no hay nada que liberar
	st = 0;
	len = 0;
	while (++i < ft_count_arg(line))
	{
		if (i != 0)
			st = st + len + 1;
		len = ft_count_arg_ind(line, st);
		dt->data[i] = malloc (sizeof(char) * (len + 1));
		if (dt->data[i] == NULL)
			return (1);//hay que ver si queremos liberar aqui
		ft_strlcpy (dt->data[i], line, st, len);
		printf ("El argumento %d:\n-%s-\n", i, dt->data[i]);
	}
	dt->data[i] = NULL;
	ft_check_arg (dt);//nuevo chequeo de los datos de entrada
	ft_free(dt, 0);//funcion que libera los argumentos
	return (0);
}

//funcion que de nuevo chequea los datos de entrada entre pipes y busca ahora:
//1- Arg entre comillas simples y dobles y los substituye por caracteres no imprimibles con su numeros para su localización
//2- Los int y out files (<< < > >>)
//3- Los cmd con sus flags 
void	ft_check_arg(t_in *dt)
{
	int	i;

	i = -1;
	while (dt->data[++i] != NULL)
	{
//		ft_simcom(dt->data[i]);//aparto la busqueda de comillas
		ft_intf(dt->data[i], dt);
	}
	printf ("El resto -%s- y de tipo %d\n", dt->intf, dt->tintf);
}

//función que va a guardar los int files que nos metan con las redirecciones y su tipo > 0 o >> 1
void	ft_intf(char *datai, t_in *dt)
{
	int	i;

	i = -1;
	while (datai[++i] != 00)
	{
		if (datai[i] == '<')
		{
			dt->tintf = 1;
			while (datai[++i] == '<')
				dt->tintf++;
			if (dt->tintf > 3)
			{
				printf ("bash: syntax error near unexpected token '<'\n");
				ft_free (dt, 1);
				exit (0);
			}
			dt->intf = (char *)malloc(sizeof(char) * ((ft_strlen(datai) - i + 1)));
			if (dt->intf == NULL)
				exit (0);//hay que ver si queremos liberar
			ft_strlcpy(dt->intf, datai, i, ft_strlen(datai) - i);
			ft_intf(dt->intf, dt);//recursiva para sacar nuevas redirecciones que anulen a las anteriores
		}
	}
}


/*
//función que analiza cada arg entre pipes buscando comillas simples, las guarda en el array bidimensional simcom y las substituye por el caracter no imprimible 30 seguido de su numero identificativo del array
void	ft_simcom(char *data_in)
{
	int	i;
	int	j;
	int	n;//cuento el numero de comillas que meten

	i = -1;
	while (data_in[++i] != 00)
	{
		if (data_in[i] == '\'')
		{
			n = 1;
			while (data_in[++i] == '\'' && data_in[i] != 00)//cuento las ' al inicio
				n++;
			printf ("el numero de comillas es: %d\n", n);
			j = 0;
			while (data_in[i] != '\'' && data_in[i] != 00)//cuento el nucleo entre '
			{
				i++;
				j++;
			}
			printf ("el nucleo mide: %d\n", j);
			while (n != 0  && data_in[i] != 00)//miro que haya igual numero de comillas que al ppio
			{
				if (data_in[i] == '\'')
					n--;
			}
			printf ("el n al final: %d\n", n);
			if (n != 0)
				exit (1);
			
		}
	}
}*/

//funcion que cuenta por cada linea escrita la cantidad de argumentos separandos por pipes y que no estén dentor de " o '. También controla si hay comillas sin cerrar y da error en ese caso
int	ft_count_arg(char *line)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	while (line[i] != 00)
	{
		if (line[i] == '\"')//localizo posibles comillas dobles
		{
			i++;
			while (line[i] != '\"' && line[i] != 00)
				i++;
			if (line[i] != '\"')
			{
				printf ("Comillas \" sin cerrar - error\n");
				exit (1);//nada para liberar de momento
			}
		}
		if (line[i] == '\'')//localizo posibles comillas simples
		{
			i++;
			while (line[i] != '\'' && line[i] != 00)
				i++;
			if (line[i] != '\'')
			{
				printf ("Comillas \' sin cerrar - error\n");
				exit (1);//nada para liberar de momento
			}
		}
		if (line[i] == '|')
			n++;
		i++;
	}
//	printf ("La n da: %d\n", n);
	return (n);
}

//funcion que cuenta el largo de cada argumento emtido entre pipes teniendo como dato donde arrancar dentro de line, lógicamente sin que estén entre comillas dobles o simples
int	ft_count_arg_ind(char *line, int st)
{
	int	i;

	i = 0;
	while (line[st + i] != 00)
	{
		if (line[st + i] == '\"')
		{
			i++;
			while (line[st + i] != '\"' && line[st + i] != 00)
				i++;
		}
		if (line[st + i] == '\'')
		{
			i++;
			while (line[st + i] != '\'' && line[st + i] != 00)
				i++;
		}
		if (line[st + i] == '|')
			break;
		i++;
	}
	return (i);
}
