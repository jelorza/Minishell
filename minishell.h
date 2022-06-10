#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define	ROJO_T 			"\x1b[31m"
# define 	RESET_COLOR		"\x1b[0m"

typedef struct	s_in
{
	char	**env;//puntero doble que guarda el env
	char	**env_name;//puntero doble con el nombre de variables de entorno
	char	**env_value;//puntero doble con los valores de variables de entorno
	char	*rootcmd;//puntero que guarda la ruta del ejecutable con el cmd y se va actualizando para cada cmd 
	char	**data;//puntero doble con los argumentos entre pipes
	char	**cmd;//puntero doble con los comd (tantos como data
	char	**red;//puntero doble con las redirecciones (tantos como data
	int		*redt;//tipo de redireccion 1 si es < y 2 si es >
	char	**rest;//puntero doble con los restos (tantos como data
	int		fdin;//guardo el fdin de entrada de datos
	int		fdout;//guardo el fdout de salida
	int		fdaux;//guardo el resultado para pasar de proceso en proceso

}	t_in;
/*
typedef struct s_list//lista para las redirecciones
{
	char	*red;//guardo el nombre del archivo
	int		n;//1 = < / 2 = << / 3 = > / 4 = >>
	s_list	*next;
}	t_list
*/
//main.c

//funciones de lectura de argumentos
//arg_utils_0.c
int		ft_break_line(char *line, t_in *dt);
int		ft_count_arg(char *line);
int		ft_count_arg_ind(char *line, int st);
void	ft_check_arg(t_in *dt);//**funcion que guarda los datos y lanza la ejecucion
void	ft_comf(char *data, int n, t_in *dt);
void	ft_redf(char *data, int n, t_in *dt);
void	ft_resf(char *data, int n, t_in *dt);

//funciones auxiliares de ayuda
//aux_utils_0.c
char	*ft_strlcpy(char *line, int st, int fn);
int		ft_strlen(char *line);
int		ft_compare_str(char *str, char *model);
char	*ft_get_name(char *str);
char	**ft_split(char *s, char c);//split con sus tres estáticas
char	*ft_strjoin(char *s1, char *s2);

//funciones de recogida del env
//env_utils_0.c
void	ft_get_env(t_in *dt, char **envp);
char	*ft_split_env_1(char *env);
char	*ft_split_env_2(char *env);
char	**ft_cut_root(t_in *dt);

//funciones de ejecucion del minishel, las que lanzan el programa
//exe_utils_0.c
int		ft_exec(t_in *dt);
int		ft_ch_buil(char *name);
int		ft_ch_cmde(t_in *dt, char *name);
int		ft_execve(t_in *dt, int n);
int		ft_ch_redir(T_in *dt, int n);

//funciones de liberacion de memoria
//free_utils_0.c
void	ft_free_0(t_in *dt);
void	ft_free_1(t_in *dt);
void	ft_free(t_in *dt, int i);

#endif
