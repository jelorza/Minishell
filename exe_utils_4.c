/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*       jelorza- <jelorza-@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:11:33 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/08/10 08:20:29 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ch_cmde_aux(t_in *dt)
{
	char	**root;
	char	*rootb;
	int		i;
	int		j;

	root = ft_cut_root(dt);
	i = -1;
	while (root[++i])
	{
		rootb = ft_strjoin(root[i], "/");
		free (root[i]);
		dt->rootcmd = ft_strjoin(rootb, dt->ncmd);
		free (rootb);
		if (access(dt->rootcmd, F_OK) == 0)
		{
			j = i;
			while (root[++j])
				free (root[j]);
			free (root);
			return (0);
		}
		ft_ch_cmde_aux_aux(dt);
	}
	free (root);
	return (-1);
}

void	ft_ch_cmde_aux_aux(t_in *dt)
{
	free (dt->rootcmd);
	dt->rootcmd = NULL;
}

char	*ft_get_name_bis(char *str)
{
	int		i;
	int		j;
	char	*strnew;

	i = 0;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '/')
			j = i;
	}
	j++;
	if (str[j] == 00)
	{
		return (NULL);
	}
	strnew = ft_strlcpy(str, j, (ft_strlen(str) - j));
	return (strnew);
}
