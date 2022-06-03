#include "minishell.h"

char	*ft_memcpy(char *dst, char *src, int n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	while (n--)
	{
		*(char *)(dst + i) = *(char *)(src + i);
		i++;
	}
	return (dst);
}

char	*ft_strdup(char *s1)
{
	char	*cpi;
	int	i;

	cpi = (char *)malloc(ft_strlen(s1) + 1 * sizeof(char));
	if (!cpi)
		return (00);
	i = 0;
	ft_memcpy(cpi, s1, ft_strlen(s1));
	*(cpi + ft_strlen(s1)) = 00;
	return (cpi);
}

void	ft_strlcpy(char *dest, char *line, int st, int len)
{
	int	i;

	i = 0;
	if (len != 0)
	{
		while (line[st + i] != 00 && i < len)
		{
			dest[i] = line[st + i];
			i++;
		}
		dest[i] = 00;
	}
	else
		dest[i] = 00;
}

int	ft_strlen(char *line)
{
	int	i;

	i = 0;
	while (line[i] != 00)
		i++;
	return (i);
}

//compara dos cadenas entre si para ver si son o no iguales - usado para salir con exit del bash considerando si lo meten con " o '
int	ft_compare_str(char *str, char *model)
{
	int	i;

	i = 0;
	while (str[i] != 00)
	{
		if (str[i] == model[i])
			i++;
		else
			break;
	}
	if (str[i] == 00)
		return (1);
	return (0);
}

char	*ft_substr(char *s, int start, int len)
{
	int	i;
	int	j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = (char *)malloc (sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	while (start--)
		i++;
	while (j < len)
	{
		ptr[j] = s[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}
