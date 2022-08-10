/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*       jelorza- <jelorza-@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:11:33 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/08/10 08:14:44 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_echo(char *s, char c)
{
	char	**r;
	int		i;
	int		j;

	i = 0;
	j = 0;
	r = (char **) malloc (sizeof(char *) * (ft_count_echo(s, c) + 1));
	if (r == NULL || s == NULL)
		return (NULL);
	r = ft_split_echo_init(s, r);
	i = -1;
	while (r[++i])
	{
		j = -1;
		while (r[i][++j])
		{
			if (r[i][j] == '!')
			{
				r[i] = ft_split_echo_aux(r[i]);
				break ;
			}
		}
	}
	return (r);
}

char	**ft_split_echo_init(char *s, char **r)
{
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	l = -1;
	while (s[i] != 00)
	{
		if (s[i] != ' ')
		{
			if (ft_count_rarus(s, i) == 0)
				j = i;
			while (s[i] != ' ' && s[i])
				i++;
			if ((s[i] == ' ' && ft_count_rarus(s, i) == 0) || s[i] == 00)
				r[++l] = ft_strlcpy (s, j, i - j);
		}
		if (s[i] != 00)
			i++;
	}
	if (l != -1)
		l++;
	r[l] = NULL;
	return (r);
}

int	ft_count_rarus(char *str, int n)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i] && i < n)
	{
		if (str[i] == '!')
			j++;
	}
	if (j % 2 == 0)
		return (0);
	return (1);
}

char	*ft_split_echo_aux(char *str)
{
	char	*aux;
	int		i;
	int		j;

	aux = (char *) malloc (sizeof (char) * (ft_strlen (str) -1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '!')
		{
			aux[j] = str[i];
			j++;
		}
		i++;
	}
	aux[j] = 00;
	free (str);
	return (aux);
}

int	ft_count_echo(char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (s[0] != c && s[0] != '\0')
		count++;
	while (s[i])
	{
		if (s[i] == '!')
		{
			i++;
			while (s[i] != '!' && s[i])
				i++;
		}
		if (s[i] == c && s[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}
