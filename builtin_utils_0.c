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
	if (i == 1)
		STATUS = ft_exe_echo(dt, n);
	else if (i == 2)
		STATUS = ft_exe_env(dt);
	else if (i == 3)
	{
		if (ft_exe_exit(dt) == -1)
			return (-1);
	}
	else if (i == 4)
		STATUS = ft_exe_export(dt);
	else if (i == 5)
		STATUS = ft_exe_pwd();
	else if (i == 6)
		STATUS = ft_exe_unset(dt);
	return (0);
}

//funcion del cd. Tiene el siguiente comportamiento
//1 - Si esta con varios comandos no hace nada en caso de que exista la ruta que hemos puesto. Si no existe si que saca mensaje de error
//2 - Solo ejecuta la opracion de cambio de ruta si es un comando unico
//Entonces, lo que hago es guardarme la ruta inicial que tengo y lanzo la ejecucion de cambio de directorio, y en caso de que haya mas comandos a parte del cd, como no ha de cambiar de directorio, pues cambio a la ruta original

int	ft_exe_echo(t_in *dt, int n)
{
	int	i = 1;

	n = 0;
	if (dt->cmdf[1] && ft_compare_str(dt->cmdf[1], "-n"))
	{
		n = 1;
		i++;
	}
	while (dt->cmdf[i])
	{
		printf("%s", dt->cmdf[i]);
		i++;
		if (dt->cmdf[i])
			printf(" ");
	}
	if (n == 0)
		printf("\n");
	return (0);
}

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
			STATUS = 1;
			return (-1);
		}
		if (dt->nc != 1) //si el comando cd no esta solo, vuelvo a la ruta donde estaba
			chdir(path);
		else//si cambio de ruta, he de cambiar el PWD y el OLDPWD del env
			ft_exe_cd_aux(dt);
	}
	STATUS = 0;
	return (0);
}

void	ft_exe_cd_aux(t_in *dt)
{
	char	path[200];

	free (dt->rootold);
	dt->rootold = ft_strlcpy(dt->root, 0, ft_strlen(dt->root));
	free (dt->root);
	getcwd(path, 200);
	dt->root = ft_strlcpy(path, 0, ft_strlen(path));
	ft_env_act(dt);
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
	if (ft_strlen_bi(dt->cmdf) > 2) //caso de demasiados argumentos en exit, y en ese caso retorna 1 y no hace nada
	{
		STATUS = 1;
		if (dt->nc == 1)
			printf ("exit\n");
		printf ("bash: exit: too many arguments\n");
		return (0);
	}
	if (dt->cmdf[1]) //calcuo el valor retornado en caso de que me metan con exit un numero
	{
		aux = ft_atoi(dt->cmdf[1]);
		if (ft_exe_exit_aux(dt, aux) == -1)
			return (-1);
	}
	if (dt->nc == 1) //caso de que exit este solo
	{
		if (STATUS == -1) //si no esta iniciado el status lo pongo a 0
			STATUS = 0;
		printf ("exit\n");
		return (-1);
	}
	return (0);
}

int	ft_exe_exit_aux(t_in *dt, long aux)
{
	if (aux == -1)
	{
		STATUS = 1;
		if (dt->nc == 1)
			printf ("exit\n");
		printf ("bash: exit: %s: numeric argument required\n", dt->cmdf[1]);
		if (dt->nc == 1)
			return (-1);
	}
	if (aux > 256)
		aux = aux % 256;
	STATUS = aux;
	return (0);
}

//funcionpara el pwd
int	ft_exe_pwd(void)
{
	char	path[200];

	if (getcwd(path, 200) == NULL) //No se cuando puede fallar la verdad, por lo que sobraria este bucle
	{
		STATUS = 1;
		return (-1);
	}
	printf ("%s\n", path);
	STATUS = 0;
	return (STATUS);
}

//funcion del export
int	ft_exe_export(t_in *dt)
{
	int	i;
	int	j;

	i = 0;
	while (dt->cmdf[++i])
	{
		j = ft_ch_name(dt->cmdf[i], 'e');
		if (j == 1)
		{
			printf ("bash: export: `%s': not a valid identifier\n", dt->cmdf[i]);
			STATUS = 1;
		}
		else if (j == 0)
		{
			if (ft_ch_name_exist(dt, dt->cmdf[i]) == 0)
			{
				dt->env = ft_update_env_plus(dt, dt->cmdf[i]);
				dt->env_name = ft_update_env_aux(dt, 'n');//actualizo el env_name;
				dt->env_value = ft_update_env_aux(dt, 'v');//actualizo el env_value;
			}
		}
	}
	if (STATUS == 1)
		return (1);
	return (0);
}

//funcion que chequea el nombre de la variable
//Retorna 0 si el nombre es válido
//Retorna 1 si el nombre no es valido
//Retorna 2 si para el export no hay un = (bash, salvo que la variable este en memoria, no hace nada) 
//*Ha de empezar por letra o _
//*El nombre no puede contener simbolos, excepto el _
int	ft_ch_name(char *str, char c)
{
	int	i;

	if (!(str[0] >= 65 && str[0] <= 90) && !(str[0] >= 97 && str[0] <= 122))//compruebo el primer char de la variable
	{
		if (str[0] != 95)
			return (1);
	}
	i = 0;
	while (str[++i] && str[i] != '=')//compruebo el nombre hasta el =, y ojo ha de tenr el igual, si no bash no hace nada
	{
		if ((str[i] >= 0 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 64) || (str[i] >= 91 && str[i] <= 96) || (str[i] >= 123 && str[i] <= 127))
		{
			if (str[i] != 95)
				return (1);
		}
	}
	if (c == 'e' && !str[i])//caso del export sin =
		return (2);
	if (c == 'u' && str[i] == '=')//caso del unset con simbolo =
		return (1);
	return (0);
}

//funcion del unset
int	ft_exe_unset(t_in *dt)
{
	int		i;

	i = 0;
	while (dt->cmdf[++i])
	{
		if (ft_ch_name(dt->cmdf[i], 'u') == 1)
		{
			printf ("bash: unset: `%s': not a valid identifier\n", dt->cmdf[i]);
			STATUS = 1;
		}
		else
		{
			if (ft_ch_name_exist_bis(dt, dt->cmdf[i]) == 1)
			{
				dt->env = ft_update_env_minus(dt, dt->cmdf[i]);
				dt->env_name = ft_update_env_aux(dt, 'n');//actualizo el env_name;
				dt->env_value = ft_update_env_aux(dt, 'v');//actualizo el env_value;
			}
		}
	}
	if (STATUS == 1)
		return (1);
	return (0);
}
