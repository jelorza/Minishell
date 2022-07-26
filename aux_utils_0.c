/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_utils_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/26 14:43:01 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*ft_copy(char *s, int i, int j);
static size_t	ft_count(char *s, char c);
static char		**ft_malloc(char *s, char c);

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

//funcion que cuenta un array bidimensional
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

//compara dos cadenas entre si para ver si son o no iguales 
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
	if (ft_compare_str(str, "grep"))
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

char	**ft_split(char *s, char c)
{
	char	**r;
	int		i;
	int		j;
	int		l;

	i = 0;
	l = 0;
	if (!s || !c)
		return (NULL);
	r = ft_malloc (s, c);
	while (s[i] != '\0' && r != NULL)
	{
		if (s[i] != c)
		{
			j = i;
			while (s[i] != c && i < ft_strlen(s))
				i++;
			r[l++] = ft_copy(s, i, j);
		}
		else
			i++;
	}
	if (r != NULL)
		r[l] = NULL;
	return (r);
}

char	**ft_split_echo(char *s, char c)
{
	char	**r;
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	l = 0;
	if (s == NULL)
		return (NULL);
	r = (char **) malloc (sizeof(char *) * (ft_count_echo(s, c) + 1));
	while (s[i] != 00)
	{
		if (s[i] != ' ')
		{
			if (ft_count_rarus(s, i) == 0)
				j = i;
			while (s[i] != ' ' && s[i])
				i++;
			if ((s[i] == ' ' && ft_count_rarus(s, i) == 0) || s[i] == 00)
			{
				r[l] = ft_strlcpy (s, j, i - j);
				l++;
			}
		}
		if (s[i] != 00)
			i++;
	}
	r[l] = NULL;
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

/*funcion que cuenta las comillas anteriores al espacio. Devuelve
0 si son pares, por lo que son comillas cerradas y no le afecta
1 si son impares y esta afectado por comillas
*/
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

static char	*ft_copy(char *s, int i, int j)
{
	char	*r;
	int		m;

	m = 0;
	r = (char *)malloc (sizeof(char) * (((i - 1) - j) + 2));
	if (r == NULL)
		return (NULL);
	while (j <= (i - 1))
		r[m++] = (char)s[j++];
	r[m] = '\0';
	return (r);
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

static size_t	ft_count(char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (s[0] != c && s[0] != '\0')
		count++;
	while (s[i + 1] != '\0')
	{
		if (s[i] == c && s[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

static char	**ft_malloc(char *s, char c)
{
	char	**r;

	r = (char **)malloc (sizeof(char *) * (ft_count(s, c) + 1));
	if (r == NULL)
		r = NULL;
	return (r);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*des;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	des = (char *)malloc ((ft_strlen (s1) + ft_strlen (s2)) + 1);
	if (des == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != 00)
		des[i] = s1[i];
	j = -1;
	while (s2[++j] != 00)
	{
		des[i] = s2[j];
		i++;
	}
	des[i] = 00;
	return (des);
}

char	*ft_strjoin_aux(char *s1, char *s2)
{
	char	*des;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	des = (char *)malloc ((ft_strlen (s1) + ft_strlen (s2)) + 1);
	if (des == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != 00)
		des[i] = s1[i];
	j = -1;
	while (s2[++j] != 00)
	{
		des[i] = s2[j];
		i++;
	}
	des[i] = 00;
	free(s1);
	free(s2);
	return (des);
}

int	ft_pipe(int *fd)
{
	int	i;

	i = pipe (fd);
	if (i == -1)
	{
		perror ("Pipe error");
		return (-1);
	}
	return (0);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork ();
	if (pid == -1)
	{
		perror ("Fork error");
		return (-1);
	}
	return (pid);
}

int	ft_close(int descr)
{
	int	i;

	i = close (descr);
	if (i == -1)
	{
		perror ("Close error");
		return (-1);
	}
	return (0);
}

int	ft_wait(int pid)
{
	int	res;
	int	st;

	res = waitpid(pid, &st, 0);
	if (res == -1)
	{
		perror ("Waitpid error");
		return (-1);
	}
	g_status = WEXITSTATUS(st);
	return (0);
}

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
