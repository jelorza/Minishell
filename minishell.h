#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define	ROJO_T 			"\x1b[31m"
# define 	RESET_COLOR		"\x1b[0m"

typedef struct s_list//lista para las redirecciones
{
	char			*file;//guardo el nombre del archivo
	int				t;//Tipo de redireccion: 1 = < / 2 = > / 3 = << / 4 = >>
	int				id;//id del comando al que afecta
	struct s_list	*next;
}	t_list;

typedef struct	s_cr//estructura para contabilizacion de redirecciones
{
	int		i;//cantidad de redirecciones de entrada, < o <<
	int		s;//cantidad de redirecciones de slaida, > o >>
	int		ti;//tipo de la ultima redireccion de entrada
	int		ts;//tipo de la ultima redireccion de salida
}	t_cr;

typedef struct	s_in
{
	char	**env;//puntero doble que guarda el env
	char	**env_name;//puntero doble con el nombre de variables de entorno
	char	**env_value;//puntero doble con los valores de variables de entorno
	char	*rootcmd;//puntero que guarda la ruta del ejecutable con el cmd y se va actualizando para cada cmd 
	char	**data;//puntero doble con los argumentos entre pipes
	char	**cmd;//puntero doble con los comd (tantos como data
	char	*ncmd;//array con el nombre del comando y se va actualizando con cada cmd 
	char	**rest;//puntero doble con los restos (tantos como data
	t_list	*red;//lista con las redirecciones y su tipo
	t_list	*head;//guardo la cabeza de la lista red
	t_list	*arg;//lista con los argumentos "redireccion" del cmd (Tipo 1 existe y Tipo 2 no existe)
	t_list	*heada;//guardo la cabeza de la lista arg
	int		fdint;//guardo el fdin de entrada que se ejecutara
	int		tint;//guardo el tipo de redireccion de entrada del ultimo file en cada pipe
	int		fdout;//guardo el fdout de salida que se ejecutara
	int		tout;//guardo el tipo de redireccion de salida del ultimo file en cada pipe
	int		fdaux;//guardo el resultado para pasar de proceso en proceso
	t_cr	*cr;//puntero a la estructura de redirecciones

}	t_in;

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
int		ft_strlen_bi(char **str);
int		ft_compare_str(char *str, char *model);
char	*ft_get_name(char *str);
char	**ft_split(char *s, char c);//split con sus tres estáticas
char	*ft_strjoin(char *s1, char *s2);
int		ft_fork(void);
int		ft_pipe(int *fd);
int		ft_close(int descr);
int		ft_wait(int pid);
int		ft_dup2(int desnew, int desold); 

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
int		ft_exe_cmd(t_in *dt, char **cmdf, int n);
int		ft_exe_cmd_st(t_in *dt, char **cmdf, int n);
int		ft_exe_cmd_int(t_in *dt, char **cmdf, int n);
int		ft_exe_cmd_end(t_in *dt, char **cmdf, int n);

//funciones de liberacion de memoria
//free_utils_0.c
void	ft_free_0(t_in *dt);
void	ft_free_1(t_in *dt);
void	ft_free(t_in *dt, int i);

//funciones auxiliares para crear o trabajar con listas
//list_utils_0.c
t_list	*ft_new(char *file, int n, int t);
void	ft_add_front(t_list **list, t_list *new);
void	ft_add_back(t_list **list, t_list *new);
void	ft_print_list(t_list *list);
void	ft_destroy_list(t_in *dt);

//funciones para gestionar las redirecciones
//red_utils_0.c
int		ft_ch_redir(t_in *dt, int n);
void	ft_ch_redir_aux0(t_list *red, t_cr *cr);
int		ft_exe_redir(t_in *dt, int n);
int		ft_exe_redir_int(t_in *dt, int n);
int		ft_exe_redir_out(t_in *dt, int n);
int		ft_exe_redir_out_aux0(t_in *dt);
int		ft_ch_arg_red(t_in *dt, int n);
//int		ft_ch_arg_red_aux(t_in *dt, int n, int nodo);
int		ft_ch_arg_red_aux(char *str, t_in *dt, int n);

#endif
