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
//		printf("---%d---\n", i);
//		printf("<%s>\n", dt->env[i]);
//		printf("<%s>\n", dt->env_name[i]);
//		printf("$%s$\n", dt->env_value[i]);
	}
	dt->env[i] = NULL;
	dt->env_name[i] = NULL;
	dt->env_value[i] = NULL;
	ft_env_act(dt);//actualizo el env si me hacen un cd (PWD & OLDPWD)
}

//funcion que me actualiza cada redline el enviroment
void	ft_env_act(t_in *dt)
{
	char	*aux;

	dt->nc = 1;
	aux = getenv("OLDPWD");
	printf ("<%s>\n", aux);
}

//funcion que extrae el nombre de las variablles de entorno y las guarda en un array bidimensional env_name
char	*ft_split_env_1(char *env)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = -1;
	while (env[i] != '=')
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
	return (root);
}

