/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/10 07:51:09 by pojea-lo         ###   ########.fr       */
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
