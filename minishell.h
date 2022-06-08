#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_in
{
	char	**env_name;//puntero doble con el nombre de variables de entorno
	char	**env_value;//puntero doble con los valores de variables de entorno
	char	**data;//puntero doble con los argumentos entre pipes
	char	**cmd;//puntero doble con los comd (tantos como data
	char	**red;//puntero doble con las redirecciones (tantos como data
	int		*redt;//tipo de redireccion 1 si es < y 2 si es >
	char	**rest;//puntero doble con los restos (tantos como data

}	t_in;

//main.c
void	ft_get_env(t_in *dt, char **envp);

//funciones de lectura de argumentos
//arg_utils_0.c
int		ft_break_line(char *line, t_in *dt);
int		ft_count_arg(char *line);
int		ft_count_arg_ind(char *line, int st);
void	ft_check_arg(t_in *dt);
void	ft_comf(char *data, int n, t_in *dt);
void	ft_redf(char *data, int n, t_in *dt);
void	ft_resf(char *data, int n, t_in *dt);

//funciones de recogida del env
//env_utils_0.c
char	*ft_split_env_1(char *env);
char	*ft_split_env_2(char *env);

//funciones auxiliares de ayuda
//aux_utils_0.c
int		ft_strlen(char *line);
void	ft_strlcpy(char *dest, char *line, int st, int fn);
int		ft_compare_str(char *str, char *model);

//funciones de liberacion de memoria
//free_utils_0.c
void	ft_free_0(t_in *dt);
void	ft_free_1(t_in *dt);
void	ft_free(t_in *dt, int i);

#endif
