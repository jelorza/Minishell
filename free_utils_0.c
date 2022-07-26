/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/26 10:58:55 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_0(t_in *dt)
{
	int	j;

	j = -1;
	if (dt->cmdf)
	{
		while (dt->cmdf[++j])
			free (dt->cmdf[j]);
		free (dt->cmdf);
		dt->cmdf = NULL;
	}
	if (dt->ncmd)
	{
		free (dt->ncmd);
		dt->ncmd = NULL;
	}
	if (dt->rootcmd)
	{
		free (dt->rootcmd);
		dt->rootcmd = NULL;
	}
	if (dt->cr)
	{
		free (dt->cr);
		dt->cr = NULL;
	}
}

void	ft_free_1(t_in *dt)
{
	int	j;

	j = -1;
	while (dt->env_name[++j] != NULL)
		free (dt->env_name[j]);
	free (dt->env_name);
	j = -1;
	while (dt->env_value[++j] != NULL)
		free (dt->env_value[j]);
	free (dt->env_value);
	j = -1;
	while (dt->env[++j] != NULL)
		free (dt->env[j]);
	free (dt->env);
	free (dt->root);
	if (dt->rootold)
		free (dt->rootold);
}

void	ft_free(t_in *dt, int i)
{
	if (i == 0)
		ft_free_0(dt);
	if (i == 1 && dt->env_name != NULL && dt->env_value != NULL)
		ft_free_1(dt);
}
