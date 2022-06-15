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
	char	**cmdfaux;//recojo en un doble puntero el cmd con sus flags para el execve
	int		i;

	cmdf = ft_split(dt->cmd[n], ' ');
	if (dt->rest[n])//amplio el cmd con los argumentos del resto
	{
		i = 0;
		int	j=0;
		while (cmdf[i])
			i++;
		cmdfaux = (char **) malloc (sizeof(char *) * (i + 2));
		while (j < i)
		{
			cmdfaux[j] = ft_strjoin("", cmdf[j]);
			free (cmdf[j]);
			j++;
		}
		free (cmdf[i]);
		free (cmdf);
		cmdfaux[i] = ft_strjoin("", dt->rest[n]);
		cmdfaux[i + 1] = NULL;
		j = 0;
		cmdf = (char **) malloc (sizeof(char *) * (i + 2));
		while (j <= i)
		{
			cmdf[j] = ft_strjoin("", cmdfaux[j]);
			free(cmdfaux[j]);
			j++;
		}
		free (cmdfaux);
		cmdf[j] = NULL;
	}
	if (ft_ch_redir(dt, n) == -1)//solo falla por el malloc y en ese caso ha de retornar hasta el final
		return (-1);
	if (ft_exe_redir(dt, n) == -1)//solo contemplo return -1 pq de falo algun malloc (errores de syntaxis tipo < > se analizan en el parseo). El resto de errores, que no exista el archivo int, falle la apertura de alguno de salida... ha de pasar al siguiente cmd habiendo enviado un error en texto
		return (-1);
	if (ft_exe_cmd(dt, cmdf, n) == -1)//lanzo la ejecución de los comandos para generar un fdaux y pasárselo al siguiente comando, si fuera el caso
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
int	ft_exe_cmd(t_in *dt, char **cmdf, int n)
{
//	t_pid	pid;

	if (n == 0 && n != ft_strlen_bi(dt->cmd) - 1)//proceso del primer comando y no es el unico
	{
		if (ft_exe_cmd_st(dt, cmdf, n) == -1)
			return (-1);
	}
	else if (n != 0 && n != (ft_strlen_bi(dt->cmd) - 1))//proceso de comandos intermedios
	{
		if (ft_exe_cmd_int(dt, cmdf, n) == -1)
			return (-1);
	}
	else if (n == ft_strlen_bi(dt->cmd) - 1)//proceso del ultimo comando o es 1 solo
	{
		if (ft_exe_cmd_end(dt, cmdf, n) == -1)
			return (-1);
	}
	return (0);
}

//EXPLICACION DE ENTRADAS:
//- Lo primero que evalua son los restos, pero no por redirecciones, si no por argumentos del propio comando que ejecuta el execve
//- Después las redirecciones
//- Después el auxiliar, si lo tiene
//- Por último la STD
//EXPLICACION DE SALIDAS:
//- Lo primero que evalúa son las redirecciones
//- Despues por defecto, el primer comando y los intermedios siempre mando su resultado al aux
//- El último comando manda la salida a la redireccion o a la estandar

//funcion que ejecuta el primer comando si hay varios
int	ft_exe_cmd_st(t_in *dt, char **cmdf, int n)
{
	int	fd[2];
	int	pid = n;

	ft_pipe (fd);
	pid = ft_fork ();
	if (pid == -1)
		return (-1);
	else if (pid == 0)//entro en el hijo
	{
		ft_close (fd[0]);
		//ENTRADAS
		if (dt->fdint > 0)//cuando tengo int file
		{
			ft_dup2 (dt->fdint, STDIN_FILENO);
			ft_close (dt->fdint);
		}
//si no tengo int file entra por el STD
		//SALIDAS
		if (dt->fdout > 0)//cuando tengo archivo de salida
		{
			ft_dup2 (dt->fdout, STDOUT_FILENO);
			ft_close (dt->fdout);
		}
		else//cuando no tengo out file
			ft_dup2 (fd[1], STDOUT_FILENO);
		ft_close (fd[1]);
		execve (dt->rootcmd, cmdf, dt->env);
		exit(0);
	}
	else//el padre
	{
		ft_close (fd[1]);
		ft_wait(pid);
		dt->fdaux = dup (fd[0]);
		ft_close (fd[0]);
	}
	return (0);
}

//funcion que ejecuta los cmd intermedios
int	ft_exe_cmd_int(t_in *dt, char **cmdf, int n)
{
	int	fd[2];
	int	pid = n;

	ft_pipe(fd);
	pid = ft_fork ();
	if (pid == 0)
	{
		ft_close (fd[0]);
		//ENTRADAS
		if (dt->fdint > 0)//tengo archivo de entrada
		{
			ft_dup2 (dt->fdint, STDIN_FILENO);
			ft_close (dt->fdint);
		}
		else if (dt->fdaux > 0)//no tengo archivo de entrada y si aux
		{
			ft_dup2 (dt->fdaux, STDIN_FILENO);
			ft_close (dt->fdaux);
		}
//en el caso que queda (cuando en el cmd anterior hay archivo de salida) recogo la STD
		//SALIDAS
		if (dt->fdout > 0)//tengo archivo de salida
		{
			ft_dup2 (dt->fdout, STDOUT_FILENO);
			ft_close (dt->fdout);
//			dt->fdaux = 0;//reseteo el aux para el siguiente cmd
		}
		else//no tengo archivo de salida. Nunca sale por STD los intermedios
			ft_dup2 (fd[1], STDOUT_FILENO);
		ft_close (fd[1]);
		execve (dt->rootcmd, cmdf, dt->env);
		exit(0);
	}
	else
	{
		ft_close (fd[1]);
		if (dt->fdaux > 0)
			ft_close (dt->fdaux);
		ft_wait(pid);
		if (fd[0] > 0)
			dt->fdaux = dup (fd[0]);
		ft_close (fd[0]);
	}
	return (0);
}

//funcion que ejecuta los comandos finales y si solo hay uno
int	ft_exe_cmd_end(t_in *dt, char **cmdf, int n)
{
	int	pid = n;

	pid = ft_fork ();
	if (pid == 0)
	{
		if (dt->fdint > 0)//si tengo archivo de entrada
		{
			ft_dup2 (dt->fdint, STDIN_FILENO);
			ft_close (dt->fdint);
		}
		else if (dt->fdaux > 0)//en caso de no tener int file pero si aux del anterior
		{
			ft_dup2 (dt->fdaux, STDIN_FILENO);
			ft_close (dt->fdaux);
		}
//por defecto si no se cumple ninguna de las anteriores coge del STD
		//SALIDAS
		if (dt->fdout > 0)//si tengo archivo de salida
		{
			ft_dup2 (dt->fdout, STDOUT_FILENO);
			ft_close (dt->fdout);
		}
//por defecto si no hay archivo de salida coge la STD
		execve (dt->rootcmd, cmdf, dt->env);
		exit(0);
	}
	else
	{
		ft_wait (pid);
		if (dt->fdaux > 0)
			ft_close (dt->fdaux);
	}
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
