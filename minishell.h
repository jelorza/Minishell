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
# define 	RESET_C			"\x1b[0m"

typedef struct s_list//lista para las redirecciones
{
	char			*data;//guardo el nombre del archivo
	int				type;//Tipo de redireccion: 1 = < / 2 = > / 3 = << / 4 = >>
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
	char	*ncmd;//array con el nombre del comando y se va actualizando con cada cmd
	char	*rootcmd;//puntero que guarda la ruta del ejecutable con el cmd y se va actualizando para cada cmd
	char	*root;//guardo la ruta inicial, para el PWD del env
	char	*rootold;//guardo la ultima ruta para el OLDPWD del env
	char	**cmdf;//array bidimensional con el comando y sus argumentos y se va actualizando
	t_list	*l_parseInit;//lista inicial de pipes
	t_list	*hdI;//cabeza de la lista pipes
	t_list	*l_parseRedir;//lista de redirecciones
	t_list	*hdR;//cabeza de la lista redirecciones
	t_list	*l_parseCmd;//lista de comandos(type 1 = builtin)
	t_list	*hd;//lista de here docs (HD)
	int		nc;//guardo el numero de cmd que hay en la lista para la funcion exit
	int		status;//guardo el valor a retornar por el programa
	int		fdint;//guardo el fdin de entrada que se ejecutara
	int		tint;//guardo el tipo de redireccion de entrada del ultimo file en cada pipe
	int		fdout;//guardo el fdout de salida que se ejecutara
	int		tout;//guardo el tipo de redireccion de salida del ultimo file en cada pipe
	int		fdaux;//guardo el resultado para pasar de proceso en proceso
	t_cr	*cr;//puntero a la estructura de redirecciones

}	t_in;

//main.c
void	ft_struct_init(t_in *dt);
void	ft_cleanAllLists(t_in *dt);

//funciones auxiliares de ayuda
//aux_utils_0.c
char	*ft_strlcpy(char *line, int st, int len);
int		ft_strlen(char *line);
int		ft_strlen_bi(char **str);
int		ft_compare_str(char *str, char *model);
char	*ft_get_name(char *str);
char	**ft_split(char *s, char c);//split con sus tres estáticas
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoinAux(char *s1, char *s2); //He tenido que crear ese join para poder liberar los dos datos de entrada (jon);
int		ft_fork(void);
int		ft_pipe(int *fd);
int		ft_close(int descr);
int		ft_wait(int pid);
int		ft_dup2(int desnew, int desold); 
void	ft_erase_aux(char **env);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *s);
char	*ft_memcpy(char *des, char *src, int n);
long	ft_atoi(char *str);

//funciones que ejecutan los builtins
//builtin_utils_o.c
int		ft_builtin(t_in *dt, int n);
int		ft_exe_cd(t_in *dt);
int		ft_exe_env(t_in *dt);
int		ft_exe_pwd(t_in *dt);
int		ft_exe_exit(t_in *dt);

//funciones de recogida del env
//env_utils_0.c
void	ft_get_env(t_in *dt, char **envp);
void	ft_env_act(t_in *dt);
char	*ft_split_env_1(char *env);
char	*ft_split_env_2(char *env);
char	**ft_cut_root(t_in *dt);

//funciones de ejecucion del minishel, las que lanzan el programa
//exe_utils_0.c
int		ft_exec(t_in *dt);
int		ft_ch_buil(char *name, t_list *list);
int		ft_ch_cmde(t_in *dt, char *name);
int		ft_execve(t_in *dt, int n);
int		ft_exe_cmd(t_in *dt, int n);
int		ft_exe_cmd_builtin(t_in *dt, int n);
int		ft_exe_cmd_exe(t_in *dt, int n);
int		ft_exe_cmd_builtin_st(t_in *dt, int n);
int		ft_exe_cmd_builtin_int(t_in *dt, int n);
int		ft_exe_cmd_builtin_end(t_in *dt, int n);
int		ft_builtin_fork(t_in *dt, int n);
int		ft_exe_cmd_builtin_st_aux(t_in *dt, int n);
int		ft_exe_cmd_exe_st(t_in *dt);
int		ft_exe_cmd_exe_int(t_in *dt);
int		ft_exe_cmd_exe_end(t_in *dt);

//funciones de liberacion de memoria
//free_utils_0.c
void	ft_free_0(t_in *dt);
void	ft_free_1(t_in *dt);
void	ft_free(t_in *dt, int i);

//funciones que realizan el here dock (HD)
//here_doc_0.c
int		ft_ch_HD(t_in *dt, int n);
void	ft_exe_null_HD(char *str);
int		ft_exe_HD(char *str, int fdint, char **env);

//funciones de linked list
//linked_list.c
t_list *ft_newNodPi(char *data, t_list **list);
t_list *ft_newNodRe(char *data, t_list **list, int id, char type);
void	ft_addNodBack(t_in *dt, char *data, char type, int id);
void	ft_printListPipe(t_list **list);
void	ft_printListCmd(t_list **list);
void	ft_printListRedir(t_list **list);
void	ft_addNodFront(t_list **list, char *data);
void	ft_cleanListPipe(t_list **list);
void	ft_cleanListCmd(t_list **list);
void	ft_cleanListRedir(t_list **list);

//funciones auxiliares para crear o trabajar con listas
//list_utils_0.c
t_list	*ft_new(char *file, int n, int t);
void	ft_add_front(t_list **list, t_list *new);
void	ft_add_back(t_list **list, t_list *new);
void	ft_print_list(t_list *list);
void	ft_destroy_list(t_list **list);
int		ft_listlen(t_list *list);

//funciones de limpieza de line (readline)
//parse_init.c
int		ft_parse_line(char *line, t_in *dt);
void	ft_remove_quot(t_in *dt);
char	*ft_expand_envs(char *line, t_in *dt);
int 	ft_charCounter(char *line, char c);
char 	*ft_checkEnv(char *line);
int		ft_checkInEnvList(char *env, t_in *dt);
char	*ft_replaceInLine(char *line, char *old, char *new);
int	ft_pipes_list(char *line, t_in *dt);
int		ft_check_quotations(char *line, int i);
void	ft_div_in_lists(t_in *dt);
int		ft_check_and_create(char *line, t_in *dt, int id);
char	ft_redir_type(char type, char nType, char nnType, char nnnType);
void	ft_printAllLists(t_in *dt);
int		ft_checkAndCreate(t_in *dt, int bool, char *data);
int		ft_checkIf39(char *line, int i); //Check if has '
char		*ft_checkIf$(char *line, int i);

//funciones para gestionar las redirecciones
//red_utils_0.c
int		ft_ch_redir(t_in *dt, int n);
void	ft_ch_redir_aux0(t_list *red, t_cr *cr);
int		ft_exe_redir(t_in *dt, int n);
int		ft_exe_redir_int(t_in *dt, int n);
int		ft_exe_redir_out(t_in *dt, int n);
int		ft_exe_redir_out_aux0(t_in *dt);
//int		ft_ch_arg_red(t_in *dt, int n);
//int		ft_ch_arg_red_aux(char *str, t_in *dt, int n);
//int		ft_ch_arg_red_aux(t_in *dt, int n, int nodo);
//int		ft_ch_arg_red_exist(t_in *dt, int n);

#endif
