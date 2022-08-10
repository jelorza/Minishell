/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_utils_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*       jelorza- <jelorza-@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:11:33 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/08/10 08:15:22 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dup2(int desold, int desnew)
{
	int	i;

	i = dup2 (desold, desnew);
	if (i == -1)
	{
		perror ("Dup error");
		return (-1);
	}
	return (0);
}

char	*ft_memcpy(char *des, char *src, int n)
{
	int	i;

	i = 0;
	if (!des && !src)
		return (NULL);
	while (i < n)
	{
		des[i] = src[i];
		i++;
	}
	des[i] = 00;
	return (des);
}

char	*ft_strdup(char *s)
{
	char	*cpi;

	if (!s)
		return (NULL);
	cpi = malloc(sizeof(char *) * ft_strlen(s) + 1);
	if (!cpi)
		return (00);
	cpi = ft_memcpy(cpi, s, ft_strlen(s));
	return (cpi);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	int		j;
	char	*ptr;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	ptr = (char *)malloc (sizeof(char) * (len - start + 1));
	if (!ptr)
		return (0);
	while (start--)
		i++;
	while (i < len)
	{
		ptr[j] = s[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

long	ft_atoi(char *str)
{
	int		i;
	long	r;

	if (!str)
		return (-1);
	i = 0;
	r = 0;
	while (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		r = (str[i] - '0') + (r * 10);
		i++;
	}
	if (str[i] == 00 || str[i] == ' ')
		return (r);
	return (-1);
}
