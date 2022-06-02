#include "minishell.h"

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
