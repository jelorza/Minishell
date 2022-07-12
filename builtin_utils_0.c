#include "minishell.h"

//Funcion que distribuye entre los builtins
//Estan todos los que piden menos el cd, porque si seguia este curso la ejecucion era en el hijo, y no se vei el resultado
int	ft_builtin(t_in *dt, int n)
{
	int		i;

	i = ft_ch_buil(dt->ncmd, dt->l_parseCmd);
//	if (i == 1)
//		dt->ret = ft_exe_echo(dt, n);
//	else if (i == 2)
//		dt->ret =  ft_exe_env(dt, n);
	if (i == 3)
	{
		ft_exe_exit(dt, n);
		return (-1);
	}
//	else if (i == 4)
//		dt->ret = ft_exe_export(dt, n);
	else if (i == 5)
		dt->ret = ft_exe_pwd(dt);
//	else if (i == 6)
//		dt->ret = ft_exe_unset(dt, n);
	if (dt->ret == -1)
		return (-1);
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
			return (-1);
		}
		if (dt->nc != 1)
			chdir(path);
	}
	return (0);
}

//funcion del exit. tiene el siguiente comportamiento:
//1 - Si es el primer comando o uno intermedio no hace nada
//2 - Si es el ultimo de muchos comandos, anula toda la salida que pudiera haber y salta a la siguiente linea de bash
//3 - Si va solo, sale del programa
//QUEDA PENDIENTE EL TEMA DEL VALOR RETORNADO
int	ft_exe_exit(t_in *dt, int n)
{
	if (dt->nc > (n + 1))//caso de que exit no haga nada
		return (0);
	else if (dt->nc == 1)
	{
		printf ("exit\n");
	}
	return (-1);
}

//funcionpara el pwd
int	ft_exe_pwd(t_in *dt)
{
	char path[200];

	if (getcwd(path, 200) == NULL)
	{
		dt->ret = 1;
		return (-1);
	}
	printf ("%s\n", path);
	return (0);
}

