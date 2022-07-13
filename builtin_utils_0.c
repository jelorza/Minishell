#include "minishell.h"

//Funcion que distribuye entre los builtins
//Estan todos los que piden menos el cd, porque si seguia este curso la ejecucion era en el hijo, y no se vei el resultado
int	ft_builtin(t_in *dt, int n)
{
	int		i;

	i = n;
	i = ft_ch_buil(dt->ncmd, dt->l_parseCmd);
	if (i == 0)
		ft_exe_cd(dt);
//	if (i == 1)
//		dt->status = ft_exe_echo(dt, n);
	else if (i == 2)
		dt->status =  ft_exe_env(dt);
	else if (i == 3)
	{
		if (ft_exe_exit(dt) == -1)
			return (-1);
	}
//	else if (i == 4)
//		dt->status = ft_exe_export(dt, n);
	else if (i == 5)
		dt->status = ft_exe_pwd(dt);
//	else if (i == 6)
//		dt->status = ft_exe_unset(dt, n);
	return (0);
}

//funcion del cd. Tiene el siguiente comportamiento
//1 - Si esta con varios comandos no hace nada en caso de que exista la ruta que hemos puesto. Si no existe si que saca mensaje de error
//2 - Solo ejecuta la opracion de cambio de ruta si es un comando unico
//Entonces, lo que hago es guardarme la ruta inicial que tengo y lanzo la ejecucion de cambio de directorio, y en caso de que haya mas comandos a parte del cd, como no ha de cambiar de directorio, pues cambio a la ruta original
int	ft_exe_cd(t_in *dt)
{
	char	path[200];
	int		fd;

	getcwd(path, 200);
	if (dt->cmdf[1])
	{
		if (chdir(dt->cmdf[1]) == -1)
		{
			fd = open(dt->cmdf[1], O_RDONLY);
			if (fd == -1)
				printf("bash: cd: %s: No such file or directory\n", dt->cmdf[1]);
			else
				printf("bash: cd: %s: Not a directory\n", dt->cmdf[1]);
			close (fd);
			dt->status = 1;
			return (-1);
		}
		if (dt->nc != 1)//si el comando cd no esta solo, vuelvo a la ruta donde estaba
			chdir(path);
		else//si cambio de ruta, he de cambiar el PWD y el OLDPWD del env
		{
			free (dt->rootold);
			dt->rootold = ft_strlcpy(dt->root, 0, ft_strlen(dt->root));
			free (dt->root);
			getcwd(path, 200);
			dt->root = ft_strlcpy(path, 0, ft_strlen(path));
			ft_env_act(dt);
		}
	}
	dt->status = 0;
	return (0);
}

//funcion que imprime el env
int	ft_exe_env(t_in *dt)
{
	int	i;

	i = -1;
	while (dt->env[++i])
		printf ("%s\n", dt->env[i]);
	return (0);
}

//funcion del exit. tiene el siguiente comportamiento:
//1 - Si es el primer comando o uno intermedio no hace nada
//2 - Si es el ultimo de muchos comandos, anula toda la salida que pudiera haber y salta a la siguiente linea de bash
//3 - Si va solo, sale del programa
int	ft_exe_exit(t_in *dt)
{
	long	aux;

	aux = 0;
	if (ft_strlen_bi(dt->cmdf) > 2)//caso de demasiados argumentos en exit, y en ese caso retorna 1 y no hace nada
	{
		dt->status = 1;
		if (dt->nc == 1)
			printf ("exit\n");
		printf ("bash: exit: too many arguments\n");
		return (0);
	}
	if (dt->cmdf[1])//calcuo el valor retornado en caso de que me metan con exit un numero
	{
		aux = ft_atoi(dt->cmdf[1]);
		if (aux == -1)
		{
			dt->status = 1;
			if (dt->nc == 1)
				printf ("exit\n");
			printf ("bash: exit: %s: numeric argument required\n", dt->cmdf[1]);
			if (dt->nc == 1)
				return (-1);
		}
		if (aux > 256)
			aux = aux % 256;
		dt->status = aux;
	}
	if (dt->nc == 1)//caso de que exit este solo
	{
		if (dt->status == -1)//si no esta iniciado el status lo pongo a 0
			dt->status = 0;
		printf ("exit\n");
		return (-1);
	}
	return (0);
}

//funcionpara el pwd
int	ft_exe_pwd(t_in *dt)
{
	char path[200];

	if (getcwd(path, 200) == NULL)//No se cuando puede fallar la verdad, por lo que sobraria este bucle
	{
		dt->status = 1;
		return (-1);
	}
	printf ("%s\n", path);
	dt->status = 0;
	return (0);
}

