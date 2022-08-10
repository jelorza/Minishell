/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_utils_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/10 07:40:55 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlcpy_itoa(char *line, char *st, int size)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(st);
	while (i < size && st[i] != 00)
	{
		line[i] = st[i];
		i++;
	}
	if (i == size)
		line[i - 1] = 00;
	else
		line[i] = 00;
	return (len);
}

char	*ft_tochar(int n, char *dest, size_t len)
{
	if (n == 0)
		*dest = 48;
	if (n < 0)
	{
		*dest = 45;
		n *= -1;
	}
	while (n > 0)
	{
		*(dest + len--) = (n % 10) + 48;
		n /= 10;
	}
	return (dest);
}	

size_t	ft_intlen(int n)
{
	size_t	intlen;

	intlen = 0;
	if (n <= 0)
	{
		n *= -1;
		intlen++;
	}
	while (n > 0)
	{
		n = n / 10;
		intlen++;
	}
	return (intlen);
}

char	*ft_itoa(int n)
{
	char	*dest;
	size_t	len;

	if (n == -2147483648)
	{
		dest = (char *) malloc (sizeof(char) * 12);
		if (dest == NULL)
			return (NULL);
		ft_strlcpy_itoa(dest, "-2147483648", 12);
		return (dest);
	}
	len = ft_intlen(n);
	dest = (char *) malloc (sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	*(dest + len--) = '\0';
	dest = ft_tochar(n, dest, len);
	return (dest);
}

char	*ft_strlcpy(char *line, int st, int len)
{
	int		i;
	char	*res;

	if (!line || st < 0 || len <= 0)
		return (NULL);
	i = 0;
	res = (char *) malloc (sizeof (char) * (len + 1));
	if (!res)
		return (NULL);
	while (line[st + i] != 00 && i < len)
	{
		res[i] = line[st + i];
		i++;
	}
	res[i] = 00;
	return (res);
}
