/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*       jelorza- <jelorza-@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:11:33 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/08/10 08:13:12 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] != 00)
		i++;
	return (i);
}

int	ft_strlen_bi(char **str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_compare_str(char *str, char *model)
{
	int	i;

	if (!str || !model)
		return (0);
	i = 0;
	while (str[i] != 00)
	{
		if (str[i] == model[i])
			i++;
		else
			break ;
	}
	if (model[i] == 00 && str[i] == 00)
		return (1);
	return (0);
}

int	ft_compare_str_cat(char *str)
{
	if (!str)
		return (0);
	if (ft_compare_str(str, "cat"))
		return (1);
	if (ft_compare_str(str, "wc"))
		return (1);
	return (0);
}

int	ft_compare_str_env(char *str, char *model)
{
	int	i;

	if (!str || !model)
		return (0);
	i = 0;
	while (str[i] != 00)
	{
		if (str[i] == model[i])
			i++;
		else
			break ;
	}
	if (model[i] == 00)
		return (1);
	return (0);
}
