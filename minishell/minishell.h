#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define	ROJO_T	"\x1b[31m"
# define	RESET_COLOR	"\x1b[m"

typedef struct s_rest
{
	int		id;
	char		*data;
	struct s_rest	*next;
	
} t_rest;

typedef struct s_cmd
{
	int		id;
	char		*data;
	struct s_cmd	*next;
	
} t_cmd;

typedef struct s_redir
{
	int		id;
	char		*data;
	char		type;
	struct s_redir	*next;
	
} t_redir;

typedef struct s_pipes
{
	int		id;
	char		*data;
	struct s_pipes	*next;
	
} t_pipes;

typedef struct s_struct{

	t_pipes		*l_parseInit;
	t_redir		*l_parseRedir;
	t_cmd		*l_parseCmd;
	t_rest		*l_parseRest;

}	t_struct;



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
char		*ft_strdup(char *s);
char		*ft_memcpy(char *des, char *src, int n);
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
void	ft_pipes_list(char *line, t_struct *structInit);
int	ft_check_quotations(char *line, int i);
void	ft_redir_list(t_struct *structInit);
void	ft_parse_line(char *line, t_struct *structInit);
char	*substr(char *s, int start, int len);
void	ft_struct_init(t_struct *structInit);
int	ft_check_and_create(char *line, t_struct *structInit, int id);
void	ft_div_in_lists(t_struct *structInit);
void	ft_cleanAllLists(t_struct *structInit);
char	ft_redir_type(char type, char nType, char nnType);
int	ft_checkRedirect(char *line, char i);

//funciones de linked list
//ft_linked_list.c
t_pipes *ft_newNodPi(char *data, t_pipes **list);
t_redir *ft_newNodRe(char *data, t_redir **list, int id, char type);
void	ft_addNodBack(t_struct *structInit, char *data, char type, int id);
void	ft_printListPipe(t_pipes **list);
void	ft_printListCmd(t_cmd **list);
void	ft_printListRedir(t_redir **list);
void	ft_printListRest(t_rest **list);
void	ft_addNodFront(t_pipes **list, char *data);
void	ft_cleanListPipe(t_pipes **list);
void	ft_cleanListCmd(t_cmd **list);
void	ft_cleanListRedir(t_redir **list);
void	ft_cleanListRest(t_rest **list);
#endif
