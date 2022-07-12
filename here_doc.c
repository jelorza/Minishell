#include "minishell.h"

//función que chequea la lista de redirecciones y mira si hay o no algun <<.
//1- Retorna 0 si no hay ninguno
//2- Retorna -1 si algo da error
//3- Retorna -2 si hay alguno
int	ft_ch_HD(t_in *dt, int n)
{
	t_list	*new;

	if (n != -1)//caso de tener un HD antes de encontrar alguna redireccion que no exista
	{
		new = ft_new(dt->l_parseRedir->data, n, 0);
		ft_add_back(&dt->hd, new);
		return (0);
	}
	else//caso de haber encontrado alguna redireccion que no existe, he de buscar si quedan HD por añadir a la lista
	{
		while (dt->l_parseRedir)
		{
			if (dt->l_parseRedir->type == 3)
			{
				new = ft_new(dt->l_parseRedir->data, n, 0);
				ft_add_back(&dt->hd, new);
			}
			dt->l_parseRedir = dt->l_parseRedir->next;
		}
	}
	ft_print_list(dt->hd);
	return (0);
}

//función que activa uno o varios HD y los va cerrando consecutivamente sin tener que guardar la información
void	ft_exe_null_HD(char *str)
{
	char *line;

	line = readline("> ");
	while (ft_compare_str(line, str) != 1)
	{
		free (line);
		line = readline("> ");
	}
	free(line);
}

//funcion que es activada cuando hay un HD predominante y va guardando linea a linea retornando el descriptor para fdint
int	ft_exe_HD(char *str, int fdint, char **env)
{
	char	*line;

	fdint = open (".aux_HD.txt.tmp", O_CREAT | O_EXCL | O_RDWR | O_APPEND, 0644);
	if (fdint == -1)
	{
		fdint = open (".aux_HD.txt.tmp", O_RDWR | O_TRUNC, 0644);
	}
	line = readline("> ");
	while (ft_compare_str(line, str) != 1)
	{
		if (write (fdint, line, ft_strlen(line)) == -1)
		{
			printf ("Write error\n");
			return (-1);
		}
		free (line);
		write (fdint, "\n", 1);//hay que añadir salto de linea
		line = readline("> ");
	}
	free(line);
	close (fdint);
	fdint = open (".aux_HD.txt.tmp", O_RDONLY);
	ft_erase_aux (env);
	return (fdint);
}

//función que borra el archivo auxiliar generado con un HD predominante
void	ft_erase_aux(char **env)
{
	char	**rm;
	int		pid;
	int		i;

	i = -1;
	rm = ft_split ("rm .aux_HD.txt.tmp", ' ');
	pid = fork();
	if (pid == 0)
	{
		execve ("/bin/rm", rm, env);
		exit(0);
	}
	else
		ft_wait(pid);
	while (rm[++i])
		free (rm[i]);
	free (rm);
}
