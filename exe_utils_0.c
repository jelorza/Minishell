#include "minishell.h"

//funcion que va a comprobar si el comando es un builtin o un ejecutable, en caso de que ninguno sea, devuelve error y pasa al siguiente comando
int	ft_exec(t_in *dt)
{
	int		i;
	char	*name;

	i = -1;
	while (dt->cmd[++i] != NULL)
	{
		name = ft_get_name(dt->cmd[i]);
		if (ft_ch_buil(name) >= 0 && ft_ch_buil(name) <= 6)//comprueba si es un builtin y devuelvo el numero del comando
		{	
			printf ("El comando %s es un builtin\n", name);
//			continua el programa ejecutandoo el builtn que toque
		}
		else if (ft_ch_cmde(dt, name) != -1)//comprueba si es un ejecutable y devuelvo el numero de la ruta del path
		{	
			printf ("El comando %s es un comando ejecutable\n", name);
			if (ft_execve (dt, i) == -1)//si falla la ejecución del comando
//				printf ("bash: %s: command error\n", name);
			free (dt->rootcmd);//libero la ruta con el cmd
		}
		else//devuelve error porque no es ni builtin ni ejecutable
			printf ("bash: %s: command not found\n", name);//mensaje de error y alsiguiente comando
		free (name);
	}
	return (0);
}

//funcion que ejecuta con el execve el comando ejecutable que corresponda (recibo en n el numero de comando que es) y mira si hay o no redirección de salida. Si hay redirección de salida la ejecuta a donde corresponda, y si no hay redireccion de salida, su resultado lo deja guardado en el fd_aux de la estructura
int	ft_execve (t_in *dt, int n)
{
	char	**cmdf;//recojo en un doble puntero el cmd con sus flags para el execve
	int		i;

	cmdf = ft_split(dt->cmd[n], ' ');
	ft_ch_redir(dt, n);
	

	i = -1;
	while (cmdf[++i] != NULL)//libero la bidimensional del comando con sus flags
		free (cmdf[i]);
	free(cmdf);
	free(dt->cr);//reseteo la estructura de redirecciones
	dt->cr = NULL;
	return (0);
}

//funcion que chequea si el comando en cuestión tiene o no redirecciones:
//1- Si tiene una o varias de entrada, todas las redirecciones de entrada comprueba si existen y la ultima la abre y deja su valor en fdin de la estructura
//2- Si tiene una o varias de salida, todas las redirecciones de salida, las abre, y la ultima la abre y deja si valor en el fdout de la estructura
int	ft_ch_redir(t_in *dt, int n)
{
	t_cr	*cr;

	cr = (t_cr *) malloc (sizeof(t_cr));//creo el puntero a la estructura principal
	dt->cr = cr;
	cr->i = 0;//todo esto lo puedo resetear con un memset y gano lineas
	cr->s = 0;
	cr->ti = 0;
	cr->ts = 0;
	dt->red = dt->head;
	while (dt->red->next != NULL)
	{
		if (dt->red->id == n)
			ft_ch_c_redir(dt->red, cr);
		dt->red = dt->red->next;
	}
	if (dt->red->id == n)
		ft_ch_c_redir(dt->red, cr);
//	printf ("Tengo %d de entrada y %d de salida, y la ultima de entrada es tipo %d y de salida %d\n", dt->cr->i, dt->cr->s, dt->cr->ti, dt->cr->ts);
	return (0);
}

//funcion que rellena la estructura de contabilizacion de redirecciones en el bucle de la lista
void	ft_ch_c_redir(t_list *red, t_cr *cr)
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

//mira si el nombre del comando pertenece a los builtins, y en caso afirmativo devuelve el numero de comando de la lista builtin
int	ft_ch_buil(char *name)
{
	char	builtins[7][7] = {"cd", "echo", "env", "exit", "export", "pwd", "unset"};
	int		i;

	i = -1;
	while (++i < 7)
	{
		if (ft_compare_str (name, builtins[i]) == 1)
			return (i);
	}
	return (-1);//el cmd no es builtin
}

//con el access comprueba si el comando es ejecutable y devuelve el numero de la ruta guardada en el array de PATH. En caso de no encontrar coincidencia devuelve -1
int	ft_ch_cmde(t_in *dt, char *name)
{
	char	**root;//rutas del PATH
	char	*rootb;//nombre de la ruta con /
	int		i;
	int		j;

	root = ft_cut_root(dt);
	i = -1;
	while (root[++i] != NULL)
	{
		rootb = ft_strjoin(root[i], "/");
		free (root[i]);
		dt->rootcmd = ft_strjoin(rootb, name);
		free (rootb);
		if (access(dt->rootcmd, F_OK) == 0)
		{
//			printf ("La ruta es:\n%s\n", dt->rootcmd);
			j = i;
			while (root[++j] != NULL)
				free (root[j]);
			free (root);
			return (i);
		}
		free (dt->rootcmd);
	}
	free (root);
	return (-1);//el cmd no es ejecutable
}
