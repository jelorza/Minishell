#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_pipes
{
	int		id;
	char		*data;
	struct s_pipes	*next;
	
} t_pipes;


typedef struct	s_in
{
	char	**env_name;//puntero doble con el nombre de variables de entorno
	char	**env_value;//puntero doble con los valores de variables de entorno
	char	**data;//puntero doble con los argumentos entre pipes
	char	*intf;//puntero que contiene el int files ultimo (los anteriores los voy machacando pues no sirven)
	int		tintf;//tipo de archivo en funcion del numero de > que haya, 1-2-3
//	char	*outf;//puntero doble con out files
//	char	**cmd;//puntero doble con cmd con sus flags

}	t_in;

//main.c
void	ft_get_env(t_in *dt, char **envp);

//funciones libft
//aux_utils_0.c
char	*ft_substr(char *s, int start, int len);
void	ft_strlcpy(char *dest, char *line, int st, int fn);
int		ft_strlen(char *line);
int		ft_compare_str(char *str, char *model);

//funciones de lectura de argumentos
//arg_utils_0.c
int		ft_break_line(char *line, t_in *dt);
int		ft_count_arg(char *line);
int		ft_count_arg_ind(char *line, int st);
void	ft_check_arg(t_in *dt);
void	ft_intf(char *datai, t_in *dt);
//void	ft_simcom(char *data_ind);

//funciones de recogida del env
//env_utils_0.c
char	*ft_split_env_1(char *env);
char	*ft_split_env_2(char *env);

//funciones de liberacion de memoria
//free_utils_0.c
void	ft_free_0(t_in *dt);
void	ft_free_1(t_in *dt);
void	ft_free(t_in *dt, int i);

//funciones de limpieza de line (readline)
//ft_parse_init.c
void	ft_between_pipes(char *line);
char	*substr(char *s, int start, int len);

//funciones de linked list
//ft_linked_list.c
t_pipes *ft_newNod(char *data);
void	ft_addNodBack(t_pipes **l_list, char *data);
void	ft_printList(t_pipes **l_list);
void	ft_addNodFront(t_pipes **l_list, char *data);

#endif
