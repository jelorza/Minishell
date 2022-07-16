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
	dt->l_parseRedir = dt->hdR;
	while (dt->l_parseRedir)
	{
		if (dt->l_parseRedir->id == n)
			ft_ch_redir_aux0(dt->l_parseRedir, cr);
		dt->l_parseRedir = dt->l_parseRedir->next;
	}
	return (0);
}

//funcion aux de la check redirecciones y rellena la estructura de contabilizacion de redirecciones en el bucle de la lista
void	ft_ch_redir_aux0(t_list *l_parseRedir, t_cr *cr)
{
		if (l_parseRedir->type == 1)
		{
			cr->i++;
			cr->ti = 1;
		}
		if (l_parseRedir->type == 3)
		{
			cr->i++;
			cr->ti = 3;
		}
		if (l_parseRedir->type == 2)
		{
			cr->s++;
			cr->ts = 2;
		}
		if (l_parseRedir->type == 4)
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
	int 	i;
	char	*cmdnex;//guardo el nombre del cmd que no existe

	i = 0;
	dt->tint = 0;//reseteo el tipo de redireccion de entrada
	cmdnex = NULL;
	dt->hd = NULL;
	dt->l_parseRedir = dt->hdR;
	while (dt->l_parseRedir)
	{
		if (dt->l_parseRedir->id == n && (dt->l_parseRedir->type == 1 || dt->l_parseRedir->type == 3))
		{
			dt->tint = dt->l_parseRedir->type;//guardo el último tipo de redireccion de entrada
			if (dt->l_parseRedir->type == 1)//caso de que sea <
			{
				if (dt->fdint > 0)//cierro el descriptor anterior para volver a abrir el definitivo 
					close (dt->fdint);
				dt->fdint = open(dt->l_parseRedir->data, O_RDONLY);
				if (dt->fdint == -1)//no existe alguna RIN
				{
					cmdnex = ft_strjoin("", dt->l_parseRedir->data);//me guardo la RIN que no existe
					n = -1;//condicion para activar en la función ch_HD que hay una redireccion que no existe
					ft_ch_HD (dt, n);//antes de retornar hay que activar el hear dock aunque no vaya a hacer nada el programa con ello
					dt->hdH = dt->hd;//me guardo la cabeza de la lista HD
					while (dt->hd)//si hay algun HD
					{
						ft_exe_null_HD(dt->hd->data);
						dt->hd = dt->hd->next;
					}
					dt->hd = dt->hdH;
					ft_destroy_list(&dt->hd);
					printf ("bash: %s: No such file or directory\n", cmdnex);
					return (-2);
				}
			}
			else if (dt->l_parseRedir->type == 3)//caso que sea <<
			{
				ft_ch_HD (dt, n);
			}
		}
		dt->l_parseRedir = dt->l_parseRedir->next;
	}
	dt->hdH = dt->hd;
	if (dt->tint == 3)//caso de que el HD sea la redireccion de entrada predominante
	{
		while (dt->hd->next)
		{
			ft_exe_null_HD(dt->hd->data);
			dt->hd = dt->hd->next;
		}
		dt->fdint = ft_exe_HD(dt->hd->data, dt->fdint, dt->env);
		if (dt->fdint == -1)
			return (-1);
	}
	else if (dt->tint != 3 && dt->hd)//caso de que un archivo de entrada sea la redireccion de entrada predominante pero exista algun HD previo
	{
		while (dt->hd)//si hay algun HD
		{
			ft_exe_null_HD(dt->hd->data);
			dt->hd = dt->hd->next;
		}
	}
	ft_destroy_list(&dt->hd);
	return (0);
}

//funcion que ejecuta las redirecciones de salida. Si falla alguna apertura de archivo, retorna -1 y si, no crea los archivos y redirecciona la salida del comando al último
//En todas las de salida (La unica diferencia entre ellas es que > machaca contenido y >> añade contenido a lo existente), lo que va a hacer es con todas las que no sean la ultima, creara los archivos, y la ultima redireccionara a la salida.
int	ft_exe_redir_out(t_in *dt, int n)
{
	dt->tout = 0;//reseteo el tipo de salida
	dt->fdout = -2;//reseteo la salida (pongo -2 pq -1 es error de open)
	dt->l_parseRedir = dt->hdR;
	while (dt->l_parseRedir)
	{
		if (dt->l_parseRedir->id == n && (dt->l_parseRedir->type == 2 || dt->l_parseRedir->type == 4))
		{
			if (ft_exe_redir_out_aux0(dt) == -1)//de momento no esta contemplado ningun retorno -1 para esta funcion pero errores de syntaxis cortan la linea entera (p. ej ls > <)
				return (-1);
		}
		dt->l_parseRedir = dt->l_parseRedir->next;
	}
//	printf ("fdout: %d\n", dt->fdout);
	return (0);
}

//funcion auxiliar de la exe_redir_out
int	ft_exe_redir_out_aux0(t_in *dt)
{
	dt->tout = dt->l_parseRedir->type;//guardo el tipo de redireccion de salida
	if (dt->fdout > 0)//cierro el desc. anterior para volver abrir el defintivo
		close (dt->fdout);
	if (dt->tout == 4)//abro archivo para añadir
		dt->fdout = open (dt->l_parseRedir->data, O_CREAT | O_EXCL | O_RDWR | O_APPEND, 0644);
	else//abro archivo para machacar
		dt->fdout = open (dt->l_parseRedir->data, O_CREAT | O_EXCL | O_RDWR | O_TRUNC, 0644);
	if (dt->fdout == -1)//el archivo ya existia he de volver a abrirlo
	{
		if (dt->tout == 4)//abro archivo para añadir
			dt->fdout = open (dt->l_parseRedir->data, O_RDWR | O_APPEND , 0644);
		else//abro archivo para machacar
			dt->fdout = open (dt->l_parseRedir->data, O_RDWR | O_TRUNC, 0644);
	}
	if (dt->fdout == -1)//fallo a la hora de abrir o crear el archivo de salida. Mandamos mensaje de error pero no retornamos -1, pq ha de seguir con el siguiente cmd
	{
		perror ("Open error\n");
		return (-1);
	}
	return (0);
}
