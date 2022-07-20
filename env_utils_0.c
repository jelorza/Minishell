#include "minishell.h"

//copia en dos array bidimensionales el enviroment al inicio
void	ft_get_env(t_in *dt, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	dt->env = (char **) malloc (sizeof(char *) * (i + 1));
	dt->env_name = (char **) malloc (sizeof(char *) * (i + 1));
	dt->env_value = (char **) malloc (sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i] != NULL)
	{
		dt->env[i] = ft_strlcpy(envp[i], 0, ft_strlen(envp[i])); 
		dt->env_name[i] = ft_split_env_1(envp[i]);
		dt->env_value[i] = ft_split_env_2(envp[i]);
		if (ft_compare_str(dt->env_name[i], "PWD"))//me guardo la ruta inicial para cambiar el env con un cd
			dt->root = ft_strlcpy(dt->env_value[i], 0, ft_strlen(dt->env_value[i]));
		if (ft_compare_str(dt->env_name[i], "OLDPWD"))//me guardo la ruta old inicial para cambiar el env con un cd
			dt->rootold = ft_strlcpy(dt->env_value[i], 0, ft_strlen(dt->env_value[i]));
	}
	dt->env[i] = NULL;
	dt->env_name[i] = NULL;
	dt->env_value[i] = NULL;
}

//funcion que me actualiza cada redline el enviroment
void	ft_env_act(t_in *dt)
{
	int	i;

	i = 0;
	while (dt->env_name[i])//busco la posicion del PWD
	{
		if (ft_compare_str(dt->env_name[i], "PWD") == 1)
			break;
		i++;
	}
	free (dt->env_value[i]);
	dt->env_value[i] = ft_strlcpy(dt->root, 0, ft_strlen(dt->root));
	free (dt->env[i]);
	dt->env[i] = ft_strjoin("PWD=", dt->env_value[i]);
	i = 0;
	while (dt->env_name[i])//busco la posicion del OLDPWD
	{
		if (ft_compare_str(dt->env_name[i], "OLDPWD") == 1)
			break;
		i++;
	}
	free (dt->env_value[i]);
	dt->env_value[i] = ft_strlcpy(dt->rootold, 0, ft_strlen(dt->rootold));
	free (dt->env[i]);
	dt->env[i] = ft_strjoin("OLDPWD=", dt->env_value[i]);
}

//funcion que extrae el nombre de las variablles de entorno y las guarda en un array bidimensional env_name
char	*ft_split_env_1(char *env)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = -1;
	while (env[i] != '=' && env[i])
		i++;
	res = (char *) malloc (sizeof(char) * (i + 1));
	if (res == NULL)
		exit(0);//ver si liberamos o no en estos casos
	while (++j < i)
		res[j] = env[j];
	res[j] = 00;
	return (res);
}

//funcion que extrae el valor de las variablles de entorno y los guarda en un array bidimensional env_value (esta identado con el env_name)
char	*ft_split_env_2(char *str)
{
	int		i;
	int		j;
	int		l;
	char	*res;

	i = 0;
	while (str[i] != '=')
		i++;
	l = i;
	while (str[l] != 00)
		l++;
	res = (char *) malloc (sizeof(char) * (l - i));
	if (res == NULL)
		exit(0);//ver si liberamos o no en estos casos
	j = 0;
	i++;
	while (j < (l - i))
	{
		res[j] = str[i + j];
		j++;
	}
	res[j] = 00;
	return (res);
}

//funcion que coge del env el path y saca todas las rutas para el access
char	**ft_cut_root(t_in *dt)
{
	int		i;
	char	**root;

	i = -1;
	root = NULL;
	while (dt->env_name[++i] != NULL)
	{
		if (ft_compare_str (dt->env_name[i], "PATH") == 1)
			break;
	}
	root = ft_split(dt->env_value[i], ':');
	root = ft_add_line(dt, root);
	return (root);
}

//funcion que me añade a las rutas de comparacion de los comandos el directorio actual para los ejecutables
char	**ft_add_line(t_in *dt, char **rootold)
{
	int		i;
	int		j;
	char	**rootnew;

	i = 0;
	rootnew = NULL;
	while (dt->env_name[i] != NULL && ft_compare_str(dt->env_name[i], "PWD") != 1)
		i++;
	if (rootold)
	{
		j = 0;
		while (rootold[j])
			j++;
		rootnew = (char **) malloc(sizeof(char *) * (j + 2));
		if (!rootnew)
			return (NULL);
		j = 0;
		while (rootold[j])
		{
			rootnew[j] = ft_strdup(rootold[j]);
			free (rootold[j]);
			j++;
		}
		free (rootold);
	}
	else
	{
		j = 0;
		rootnew = (char **) malloc(sizeof(char *) * (2));
		if (!rootnew)
			return (NULL);
	}
	rootnew[j] = ft_strdup(dt->env_value[i]);
	j++;
	rootnew[j] = NULL;
	return (rootnew);
}

//funcion que chequea si ya existe la variable en el env y en ese caso solo modifica su valor
int	ft_ch_name_exist(t_in *dt, char *str)
{
	char	*name;
//	char	*value;
	int		i;

	name = ft_split_env_1(str);
	i = 0;
	while (dt->env_name[i])
	{
		if (ft_compare_str(name, dt->env_name[i]) == 1)
			break ;
		i++;
	}
	if (i != ft_strlen_bi(dt->env_name))
	{
		ft_change_value (dt, name, str);
		free (name);
		return (1);
	}
	else
	{
		free (name);
		return (0);
	}
}

//funcion que como la variable ya existe en el env y no se ha de crear, solo modifica su valor
void	ft_change_value (t_in *dt, char *name, char *str)
{
	int		i;
	char	*valuenew;
	char 	*aux;
	
	i = 0;
	while (dt->env_name[i])
	{
		if (ft_compare_str(name, dt->env_name[i]) == 1)
			break ;
		i++;
	}
	valuenew = ft_split_env_2(str);
	free (dt->env_value[i]);
	dt->env_value[i] = ft_strdup(valuenew);
	free (valuenew);
	free (dt->env[i]);
	aux = ft_strjoin(name, "=");
	dt->env[i] = ft_strjoin(aux, dt->env_value[i]);
	free (aux);
}

//funcion que añade variables de entorno al env
char	**ft_update_env_plus(t_in *dt, char *str)
{
	char	**envnew;
	int		i;

	i = 0;
	while (dt->env[i])
		i++;
	envnew = (char **) malloc (sizeof(char *) * (i + 3));
	if (!envnew)
		return (NULL);
	i = -1;
	while (dt->env[++i])
	{
		envnew[i] = ft_strdup(dt->env[i]);
		free (dt->env[i]);
	}
	free (dt->env);
	envnew[i] = ft_strdup(str);
	envnew[++i] = NULL;
//	ft_update_env_rest
	return (envnew);
}
