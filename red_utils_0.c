#include "minishell.h"

//funcion que chequea si el comando en cuestión tiene o no redirecciones:
//Primero analizará si tiene o no redireccion de entrada. 
//Luego mira redirecciones de salida.
//Retorna -1 en caso de Malloc error
int	ft_ch_redir(t_in *dt, int n)
{
	t_cr	*cr;

	dt->fdint = -2;//reinicio el fdint
	cr = (t_cr *) malloc (sizeof(t_cr));//creo el puntero a la estructura de redirecciones en la ppal
	if (!cr)
	{
		perror ("Malloc error\n");
		return (-1);
	}
	dt->cr = cr;
	cr->i = 0;//todo esto lo puedo resetear con un memset y gano lineas
	cr->s = 0;
	cr->ti = 0;
	cr->ts = 0;
	dt->red = dt->head;
	while (dt->red)
	{
		if (dt->red->id == n)
			ft_ch_redir_aux0(dt->red, cr);
		dt->red = dt->red->next;
	}
	return (0);
}

//funcion aux de la check redirecciones y rellena la estructura de contabilizacion de redirecciones en el bucle de la lista
void	ft_ch_redir_aux0(t_list *red, t_cr *cr)
{
		if (red->t == 1)
		{
			cr->i++;
			cr->ti = 1;
		}
		if (red->t == 3)
		{
			cr->i++;
			cr->ti = 3;
		}
		if (red->t == 2)
		{
			cr->s++;
			cr->ts = 2;
		}
		if (red->t == 4)
		{
			cr->s++;
			cr->ts = 4;
		}
}

//funcion que va a ejecutar las redirecciones:
int	ft_exe_redir(t_in *dt, int n)
{
	int	i;

	i = ft_exe_redir_int(dt, n);
	if (i == -1)
		return (-1);
	else if (i == -2)
		return (-2);//caso de que no exista el archivo
	if (ft_exe_redir_out(dt, n) == -1)
		return (-1);
	return (0);
}

//funcion que ejecuta las redirecciones de entrada. Primero mirara si es < o <<.
//1 - Si es <: comprobará si existe el archivo o archivos, y en caso de que alguno no existe mandará mensaje de error y retornará -2. Si existen todos, redirecciona el fdint de la estructura ppal al archivo de entrada último
//2 - Si es <<:
int	ft_exe_redir_int(t_in *dt, int n)
{
	dt->tint = 0;//reseteo el tipo de entrada
	dt->red = dt->head;
	while (dt->red)
	{
		if (dt->red->id == n && (dt->red->t == 1 || dt->red->t == 3))
		{
			dt->tint = dt->red->t;//guardo el último tipo de redireccion de entrada
			if (dt->red->t == 1)//caso de que sea <
			{
				if (dt->fdint > 0)//cierro el descriptor anterior para volver a abrir el definitivo 
					close (dt->fdint);
				dt->fdint = open(dt->red->file, O_RDONLY);
				if (dt->fdint == -1)//aqui hay que añadir la condición de que no haya ningun hear dock
				{
//					ft_hear_dock (dt, n);//antes de retornar hay que activar el hear dock aunque no vaya a hacer nada el programa con ello
					printf ("bash: %s: No such file or directory\n", dt->red->file);
					return (-2);
				}
			}
			if (dt->red->t == 3)//caso que sea <<
			{
				printf ("Caso de hear dock\n");//Lo dejo para luego!!!
//Aquí habrá que analizar si la redirección predominante es < o <<.
//1 - Si es <: habrá que comprobar si existen todos los < anteriores y abrir todos los << e ir cerrandolos consecutivamente, pero la información solo la cogera del < ultimo
//2 - Si es <<: habrá que abrir todos los << e ir cerrandolos consecutivamente, y cogerá la informacion del último de ellos. Con los < tendrá que comprobar si existen todos, y en caso de que alguno no existe, una vez cerrados todos los << dara el mensaje de error 
			}
		}
		dt->red = dt->red->next;
	}
	if (dt->fdint == -2)
		dt->fdint = dt->fdint;
	return (0);
}

//funcion que ejecuta las redirecciones de salida. Si falla alguna apertura de archivo, retorna -1 y si, no crea los archivos y redirecciona la salida del comando al último
//En todas las de salida (La unica diferencia entre ellas es que > machaca contenido y >> añade contenido a lo existente), lo que va a hacer es con todas las que no sean la ultima, creara los archivos, y la ultima redireccionara a la salida.
int	ft_exe_redir_out(t_in *dt, int n)
{
	dt->tout = 0;//reseteo el tipo de salida
	dt->fdout = -2;//reseteo la salida (pongo -2 pq -1 es error de open)
	dt->red = dt->head;
	while (dt->red)
	{
		if (dt->red->id == n && (dt->red->t == 2 || dt->red->t == 4))
		{
			if (ft_exe_redir_out_aux0(dt) == -1)//de momento no esta contemplado ningun retorno -1 para esta funcion pero errores de syntaxis cortan la linea entera (p. ej ls > <)
				return (-1);
		}
		dt->red = dt->red->next;
	}
//	printf ("fdout: %d\n", dt->fdout);
	return (0);
}

//funcion auxiliar de la exe_redir_out
int	ft_exe_redir_out_aux0(t_in *dt)
{
	dt->tout = dt->red->t;//guardo el tipo de redireccion de salida
	if (dt->fdout > 0)//cierro el desc. anterior para volver abrir el defintivo
		close (dt->fdout);
	if (dt->tout == 4)//abro archivo para añadir
		dt->fdout = open (dt->red->file, O_CREAT | O_EXCL | O_RDWR | O_APPEND, 0644);
	else//abro archivo para machacar
		dt->fdout = open (dt->red->file, O_CREAT | O_EXCL | O_RDWR | O_TRUNC, 0644);
	if (dt->fdout == -1)//el archivo ya existia he de volver a abrirlo
	{
		if (dt->tout == 4)//abro archivo para añadir
			dt->fdout = open (dt->red->file, O_RDWR | O_APPEND , 0644);
		else//abro archivo para machacar
			dt->fdout = open (dt->red->file, O_RDWR | O_TRUNC, 0644);
	}
	if (dt->fdout == -1)//fallo a la hora de abrir o crear el archivo de salida. Mandamos mensaje de error pero no retornamos -1, pq ha de seguir con el siguiente cmd
	{
		perror ("Open error\n");
		return (-1);
	}
	return (0);
}

//funcion que chequea los argumentos de redireccion:
//0- Si da error de mallocs o cualquier otro error retorno -1.
//1- Si tiene arg de redireccion y existen, habría que mirar si hay HD, para lanzarlo en vacio, y no coger las RINT posibles que haya. En este caso retorna 0.
//2- Si tienen arg de red. Y no existen, habría que mirar si hay HD, para lanzarlo en vacio, y mandar mensaje de error. Retorno -3.
//3- Si no hay argumentos, seguir el curso de las redirecciones. Retorno -2
int	ft_ch_arg_red(t_in *dt, int n)
{
	int		argt;
//	char	prueba[100] = "lsse - -la wer 'ter' '-' - 'er' pol";
//	char	prueba[100] = "lsse '    ter  %' ";
//	char	prueba[100] = "lsse -la";
//	char	prueba[100] = "ls 'adios'";

//	argt = ft_ch_arg_red_aux(prueba, dt, n);
	argt = ft_ch_arg_red_aux(dt->acmd, dt, n);
	if (argt == -2)//caso de que no hay argumentos
		return (-2);
	argt = ft_ch_arg_red_exist(dt, n);
	if (argt == -2)//caso de que no existe algun argumento
		return (-3);
	return (0);
}

//funcion que detecta si hay redirecciones en esos argumentos. Si hay retorna 0 y si no retorna -2.
int	ft_ch_arg_red_aux(char *str, t_in *dt, int n)
{
	char	*argt;
	t_list	*new;
	int		i;
	int		st;
	int		len;

	i = 0;
	argt = NULL;
	dt->arg = NULL;
//	printf ("str: %s\n", str);
	while (str[i])
	{
		while (str[i] != ' ' && str[i])
			i++;
		if (!str[i])
			break;
		i++;
		if (str[i] == '-')
		{
			if (str[i + 1] && str[i + 1] == ' ')//caso de que sea solo un guion
			{
				argt = ft_strlcpy("-", 0, 1);
				new = ft_new(argt, n, 0);//de primeras meto tipo 0
				ft_add_back(&dt->arg, new);
			}
			while (str[i] != ' ' && str[i])
				i++;
			if (!str[i])
				break;
		}
		else if (str[i] != '\'' && str[i] != '"')//cuando el arg. no esta entre comillas
		{
			st = i;
			while (str[i] && str[i] != ' ')
				i++;
			len = i - st;
			argt = ft_strlcpy(str, st, len);
			new = ft_new(argt, n, 0);//de primeras meto tipo 0
			ft_add_back(&dt->arg, new);
		}
		else//cuando el argumento esta entre comillas
		{
			if (str[i] == '\'')
			{
				st = ++i;
				while (str[i] && str[i] != '\'')
					i++;
				len = i - st;
				argt = ft_strlcpy(str, st, len);
				new = ft_new(argt, n, 0);//de primeras meto tipo 0
				ft_add_back(&dt->arg, new);
			}
			else if (str[i] == '"')
			{
				st = ++i;
				while (str[i] && str[i] != '"')
					i++;
				len = i - st;
				argt = ft_strlcpy(str, st, len);
				new = ft_new(argt, n, 0);//de primeras meto tipo 0
				ft_add_back(&dt->arg, new);
			}
		}
//		i++;
	}
	if (dt->arg != NULL)
	{
		dt->heada = dt->arg;
//		ft_print_list(dt->arg);
		return (0);
	}
	return (-2);
}

//funcion que va a detectar si las redirecciones de argumento que hay, existen o no. Si existen todas, abro la última y la meto en el fdint de la estructura y retorna 0, y si no existe alguna, retorna -2
int	ft_ch_arg_red_exist(t_in *dt, int n)
{
	dt->arg = dt->heada;
	while (dt->arg)
	{
		if (dt->arg->id == n)
		{
			if (dt->fdint > 0)//cierro el descriptor anterior para volver a abrir el definitivo
				close (dt->fdint);
			dt->fdint = open(dt->arg->file, O_RDONLY);
/*			if (dt->fdint == -1)//caso de que no exista algun argumento
			{
//				ft_hear_dock (dt, n);//antes de retornar hay que activar el hear dock aunque no vaya a hacer nada el programa con ello
				printf ("%s: %s: No such file or directory\n", dt->ncmd, dt->arg->file);
				return (-2);
			}
*/		}
		dt->arg = dt->arg->next;
	}
	return (0);
}
