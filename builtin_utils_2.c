/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*       jelorza- <jelorza-@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:11:33 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/08/10 08:16:27 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exe_unset(t_in *dt)
{
	int		i;

	i = 0;
	while (dt->cmdf[++i])
	{
		if (ft_ch_name(dt->cmdf[i], 'u') == 1)
		{
			printf ("bash: unset: `%s': not a valid identifier\n", dt->cmdf[i]);
			g_status = 1;
		}
		else
		{
			if (ft_ch_name_exist_bis(dt, dt->cmdf[i]) == 1)
			{
				dt->env = ft_update_env_minus(dt, dt->cmdf[i]);
				dt->env_name = ft_update_env_aux(dt, 'n');
				dt->env_value = ft_update_env_aux(dt, 'v');
			}
		}
	}
	if (g_status == 1)
		return (1);
	return (0);
}
