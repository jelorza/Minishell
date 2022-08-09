/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/09 18:17:42 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_compare_str(dt->env_name[i], "PWD"))
			dt->root = ft_strlcpy(dt->env_value[i], 0,
					ft_strlen(dt->env_value[i]));
		if (ft_compare_str(dt->env_name[i], "OLDPWD"))
			dt->rootold = ft_strlcpy(dt->env_value[i], 0,
					ft_strlen(dt->env_value[i]));
	}
	dt->env[i] = NULL;
	dt->env_name[i] = NULL;
	dt->env_value[i] = NULL;
}

void	ft_env_act(t_in *dt)
{
	int	i;

	i = 0;
	while (dt->env_name[i])
	{
		if (ft_compare_str(dt->env_name[i], "PWD") == 1)
			break ;
		i++;
	}
	free (dt->env_value[i]);
	dt->env_value[i] = ft_strlcpy(dt->root, 0, ft_strlen(dt->root));
	free (dt->env[i]);
	dt->env[i] = ft_strjoin("PWD=", dt->env_value[i]);
	i = 0;
	while (dt->env_name[i])
	{
		if (ft_compare_str(dt->env_name[i], "OLDPWD") == 1)
			break ;
		i++;
	}
	free (dt->env_value[i]);
	dt->env_value[i] = ft_strlcpy(dt->rootold, 0, ft_strlen(dt->rootold));
	free (dt->env[i]);
	dt->env[i] = ft_strjoin("OLDPWD=", dt->env_value[i]);
}

char	*ft_split_env_1(char *env)
{
	int		i;
	int		j;
	char	*res;

	if (!env)
		return (NULL);
	i = 0;
	j = -1;
	while (env[i] != '=' && env[i])
		i++;
	res = (char *) malloc (sizeof(char) * (i + 1));
	if (res == NULL)
		return (NULL);
	while (++j < i)
		res[j] = env[j];
	res[j] = 00;
	return (res);
}

char	*ft_split_env_2(char *str)
{
	int		i;
	int		j;
	int		l;
	char	*res;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (!str[i])
		return (NULL);
	l = i;
	while (str[l] != 00)
		l++;
	res = (char *) malloc (sizeof(char) * (l - i));
	if (res == NULL)
		return (NULL);
	j = -1;
	i++;
	while (++j < (l - i))
		res[j] = str[i + j];
	res[j] = 00;
	return (res);
}

char	**ft_cut_root(t_in *dt)
{
	int		i;
	char	**root;

	i = -1;
	root = NULL;
	while (dt->env_name[++i] != NULL)
	{
		if (ft_compare_str (dt->env_name[i], "PATH") == 1)
			break ;
	}
	root = ft_split(dt->env_value[i], ':');
	root = ft_add_line(dt, root);
	return (root);
}

char	**ft_add_line(t_in *dt, char **rootold)
{
	int		j;
	char	**rootnew;

	j = 0;
	rootnew = NULL;
	if (rootold)
	{
		while (rootold[j])
			j++;
		rootnew = (char **) malloc(sizeof(char *) * (j + 2));
		j = -1;
		while (rootold[++j])
		{
			rootnew[j] = ft_strdup(rootold[j]);
			free (rootold[j]);
		}
		free (rootold);
	}
	else
		rootnew = (char **) malloc(sizeof(char *) * (2));
	rootnew[j] = ft_strdup(dt->env_value[ft_add_line_aux(dt)]);
	j++;
	rootnew[j] = NULL;
	return (rootnew);
}

int	ft_add_line_aux(t_in *dt)
{
	int	i;

	i = 0;
	while (dt->env_name[i] != NULL
		&& ft_compare_str(dt->env_name[i], "PWD") != 1)
		i++;
	return (i);
}

int	ft_ch_name_exist(t_in *dt, char *str)
{
	char	*name;
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

void	ft_change_value(t_in *dt, char *name, char *str)
{
	int		i;
	char	*valuenew;
	char	*aux;

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

char	**ft_update_env_plus(t_in *dt, char *str)
{
	char	**envnew;
	int		i;

	i = 0;
	while (dt->env[i])
		i++;
	envnew = (char **) malloc (sizeof(char *) * (i + 2));
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
	return (envnew);
}

int	ft_ch_name_exist_bis(t_in *dt, char *str)
{
	char	*name;
	int		i;

	name = ft_split_env_1(str);
	i = -1;
	while (dt->env_name[++i])
	{
		if (ft_compare_str(name, dt->env_name[i]) == 1)
			break ;
	}
	if (i != ft_strlen_bi(dt->env_name))
	{
		free (name);
		return (1);
	}
	free (name);
	return (0);
}

//funcion que quita, si existe la variable, la variable del env
char	**ft_update_env_minus(t_in *dt, char *str)
{
	char	**envnew;
	char	*name;
	int		i;
	int		j;

	name = ft_split_env_1(str);
	envnew = (char **) malloc (sizeof(char *) * (ft_strlen_bi(dt->env)));
	i = -1;
	while (ft_compare_str(name, dt->env_name[++i]) != 1)
	{
		envnew[i] = ft_strdup(dt->env[i]);
		free (dt->env[i]);
	}
	free (dt->env[i]);
	dt->env[i] = NULL;
	j = i;
	while (dt->env[++j])
	{
		envnew[i++] = ft_strdup(dt->env[j]);
		free (dt->env[j]);
	}
	envnew[i] = NULL;
	free (dt->env);
	free (name);
	return (envnew);
}

char	**ft_update_env_aux(t_in *dt, char c)
{
	int		i;
	char	**env_new;

	i = ft_update_env_aux_aux(dt, c);
	env_new = (char **) malloc (sizeof(char *) * (i + 2));
	i = -1;
	while (dt->env[++i] != NULL)
	{
		if (c == 'n')
			env_new[i] = ft_split_env_1(dt->env[i]);
		else if (c == 'v')
			env_new[i] = ft_split_env_2(dt->env[i]);
	}
	env_new[i] = NULL;
	return (env_new);
}

int	ft_update_env_aux_aux(t_in *dt, char c)
{
	int	i;

	i = -1;
	if (c == 'n')
	{
		while (dt->env_name[++i] != NULL)
			free(dt->env_name[i]);
		free (dt->env_name);
	}
	if (c == 'v')
	{
		while (dt->env_value[++i] != NULL)
			free(dt->env_value[i]);
		free (dt->env_value);
	}
	return (i);
}
