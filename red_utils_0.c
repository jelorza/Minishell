#include "minishell.h"

//funcion que va a ejecutar las redirecciones:
int	ft_exe_redir(t_in *dt, int n)
{
//	int	i;

	if (ft_exe_redir_int(dt, n) == -1)
		return (-1);
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
	dt->fdint = -2;//reseteo la entrada
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
					printf ("bash: %s: No such file or directory\n", dt->red->file);
//					ft_hear_dock (dt, n);//antes de retornar hay que activar el hear dock aunque no vaya a hacer nada el programa con ello
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
//	printf ("fdint: %d\n", dt->fdint);
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
		perror ("Open error\n");
	return (0);
}


//funcion que chequea si el comando en cuestión tiene o no redirecciones y carga los valores de la estructura cr (contabilización de redirecciones) en caso afirmativo
int	ft_ch_redir(t_in *dt, int n)
{
	t_cr	*cr;

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
//	printf ("Tengo %d de entrada y %d de salida, y la ultima de entrada es tipo %d y de salida %d\n", dt->cr->i, dt->cr->s, dt->cr->ti, dt->cr->ts);
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
