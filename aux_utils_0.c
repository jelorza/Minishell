#include "minishell.h"

static char	*ft_copy(char *s, int i, int j);
static size_t	ft_count(char *s, char c);
static char	**ft_malloc(char *s, char c);

char	*ft_strlcpy(char *line, int st, int len)
{
	int		i;
	char	*res;

	i = 0;
	res = (char *) malloc (sizeof (char) * (len + 1));
	if (!res)
		exit (0);
	if (len != 0)
	{
		while (line[st + i] != 00 && i < len)
		{
			res[i] = line[st + i];
			i++;
		}
		res[i] = 00;
	}
	else
		res[i] = 00;
	return (res);
}

int	ft_strlen(char *line)
{
	int	i;

	i = 0;
	while (line[i] != 00)
		i++;
	return (i);
}

//compara dos cadenas entre si para ver si son o no iguales 
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

//funcion que extrae mallocado solamente el nombre de la cadena comando
char	*ft_get_name(char *str)
{
	char	*name;
	int		i;

	i = -1;
	while (str[++i] != 00)
	{
		if (str[i] == ' ')
			break;
	}
	name = ft_strlcpy(str, 0, i);
	return (name);
}

//split con sus tres estáticas
char	**ft_split(char *s, char c)
{
	char	**r;
	int		i;
	int		j;
	int		l;

	i = 0;
	l = 0;
	if (s == NULL)
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
