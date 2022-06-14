#include "minishell.h"

//funcion que va a comprobar si el comando es un builtin o un ejecutable, en caso de que ninguno sea, devuelve error y pasa al siguiente comando
int	ft_exec(t_in *dt)
{
	int		i;
	char	*name;

	i = -1;
	dt->fdaux = -2;//inicio el descriptor auxiliar
	while (dt->cmd[++i])
	{
		name = ft_get_name(dt->cmd[i]);
		if (ft_ch_buil(name) >= 0 && ft_ch_buil(name) <= 6)//comprueba si es un builtin y devuelvo el numero del comando builtin y si no -1
		{	
			printf ("El comando %s es un builtin\n", name);
//			continua el programa ejecutandoo el builtn que toque
		}
		else if (ft_ch_cmde(dt, name) != -1)//comprueba si es un ejecutable y devuelvo el numero de la ruta del path
		{	
			printf ("El comando %s es un comando ejecutable\n", name);
			if (ft_execve (dt, i) == -1)//si falla la ejecución del comando o error de syntaxis
			{
				printf ("bash: %s: COMMAND ERROR\n", name);//NO SE QUE PONE BASH EN ESTE CASO Y TAMPOCO SE SI CORTA O SIGUE EJECUTANDO EL RESTO DE COMANDOS
				free (dt->rootcmd);//libero la ruta con el cmd
				return (-1);
			}
			free (dt->rootcmd);//libero la ruta con el cmd
		}
		else//devuelve error porque no es ni builtin ni ejecutable
			printf ("bash: %s: command not found\n", name);//mensaje de error y al siguiente comando
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
	if (ft_ch_redir(dt, n) == -1)//solo falla por el malloc y en ese caso ha de retornar hasta el final
		return (-1);
	if (ft_exe_redir(dt, n) == -1)//solo contemplo return -1 pq de falo algun malloc (errores de syntaxis tipo < > se analizan en el parseo). El resto de errores, que no exista el archivo int, falle la apertura de alguno de salida... ha de pasar al siguiente cmd habiendo enviado un error en texto
		return (-1);
	if (ft_exe_cmd(dt, cmdf) == -1)//lanzo la ejecución de los comandos para generar un fdaux y pasárselo al siguiente comando, si fuera el caso
		return (-1);




	i = -1;
	while (cmdf[++i])//libero la bidimensional del comando con sus flags
		free (cmdf[i]);
	free(cmdf);
	if (dt->red)
	{
		free(dt->cr);//reseteo la estructura de redirecciones
		dt->cr = NULL;
	}
	return (0);
}

//función que ejecuta el comando con los fdint y fdout de la estructura. Retornará -1 en caso de error
int	ft_exe_cmd(t_in *dt, char **cmdf)
{
	int	fd[2];//descriptor del pipe

	if (pipe (fd) == -1)
	{
		perror ("Pipe error\n");
		return (-1);
	}
	if (dt-> 
	execve (dt->rootcmd, cmdf, dt->env);
	return (0);
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
	while (root[++i])
	{
		rootb = ft_strjoin(root[i], "/");
		free (root[i]);
		dt->rootcmd = ft_strjoin(rootb, name);
		free (rootb);
		if (access(dt->rootcmd, F_OK) == 0)
		{
//			printf ("La ruta es:\n%s\n", dt->rootcmd);
			j = i;
			while (root[++j])
				free (root[j]);
			free (root);
			return (i);
		}
		free (dt->rootcmd);
	}
	free (root);
	return (-1);//el cmd no es ejecutable
}
