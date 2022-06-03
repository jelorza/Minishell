#include "minishell.h"

//acabo de probar que estoy metiendo bien y sacando bien los datos de la lista de dentro de la estructura. Ahora me queda implantar la funcion de los nodos.

void	ft_parse_line(char *line, t_struct *structInit)
{
	ft_between_pipes(line,&structInit->l_parseInit);
//	ft_redirects(line,structInit);
}	

void	ft_between_pipes(char *line, t_pipes **list)
{
	int	i;
	int	z;
	char 	*data;
	
	i = 0;
	z = 0;
	while (line[i])
	{
		while(line[i] != '|' && line[i])
		{
			if (line[i] == 39)
			{
				if (line[++i])
				{
					printf("existo\n");
					while(line[i] != 39 && line[i])
						i++;
				}
				if (!line[i])
				{
					printf("ERROR:solo abro commillas pero no las cierro por lo que me tengo que quedar colgado\n");
					exit (1);	
				}
			}
			else if (line[i] == '"')
			{
				if (line[++i])
				{
					printf("existo\n");
					while(line[i] != '"' && line[i])
						i++;
				}
				if (!line[i])
				{
					printf("ERROR:solo abro commillas pero no las cierro por lo que me tengo que quedar colgado\n");
					exit (1);	
				}
			}
			i++;
		}
		data = ft_substr(line, z, i-z);
		ft_addNodBack(list, data);
		if (line[i] == '|' )
			i++;
		z = i;
		i++;
	}
	ft_printList(list);
	printf("Elimino la lista\n");
	ft_cleanList(list);
	ft_printList(list);
}




