#include "minishell.h"
/*
void	ft_addNod_back(t_pipes **l_parseInit, char *line, int i, int z)
{
	char *data;

	data = malloc(sizeof(char*) * i-z);
	ft_strlcpy(
}
*/
void	ft_between_pipes(char *line)
{
	t_pipes *l_parseInit = NULL;
	int i;
	int z;

	char *data;

	i = 0;
	z = 0;
	while (line[i])
	{
		while(line[i] != '|' && line[i])
		{
			if (line[i] == 39)
			{ 
				while (line[++i] != 39 && line[i])
					i++;
			}
			else if (line[i] == '"')
			{
				while(++line[i] != '"' && line[i])
					i++;
			}
			i++;
		}
		data = ft_substr(line, z, i-z);
		printf("%s\n", data);
//		free(data);
		ft_addNodBack(&l_parseInit, data);
		if (line[i] == '|' )
			i++;
		z = i;
		i++;
	}
	printf("%s\n",line);
	ft_printList(&l_parseInit);
//	ft_cleanList();
}




