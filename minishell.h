/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/10 07:26:56 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <signal.h>

int	g_status;

typedef struct s_list
{
	char			*data;
	int				type;
	int				id;
	struct s_list	*next;
}	t_list;

typedef struct s_cr
{
	int		i;
	int		s;
	int		ti;
	int		ts;
}	t_cr;

typedef struct s_in
{
	char	**env;
	char	**env_name;
	char	**env_value;
	char	*ncmd;
	char	*rootcmd;
	char	*root;
	char	*rootold;
	char	**cmdf;
	char	**cmdf_echo;
	t_list	*l_parse_init;
	t_list	*hd_i;
	t_list	*l_parse_redir;
	t_list	*hd_r;
	t_list	*l_parse_cmd;
	t_list	*hd_c;
	t_list	*hd;
	t_list	*hd_h;
	int		nc;
	int		status;
	int		fdint;
	int		tint;
	int		fdout;
	int		tout;
	int		fdaux;
	int		an;
	t_cr	*cr;

}	t_in;

void	ft_struct_init(t_in *dt, char **envp);
void	ft_clean_all_lists(t_in *dt);
char	*ft_strlcpy(char *line, int st, int len);
int		ft_strlcpy_itoa(char *line, char *st, int size);
int		ft_strlen(char *line);
int		ft_strlen_bi(char **str);
int		ft_compare_str(char *str, char *model);
void	ft_cmp_replace(char *env[3], t_in *dt, int is_env);
int		ft_compare_str_cat(char *str);
int		ft_compare_str_env(char *str, char *model);
char	*ft_get_name_bis(char *str);
char	**ft_split(char *s, char c);
char	**ft_split_echo(char *s, char c);
char	**ft_split_echo_init(char *s, char **r);
char	*ft_split_echo_aux(char *s);
int		ft_count_rarus(char *s, int n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_aux(char *s1, char *s2);
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
int		ft_count_echo(char *s, char c);
char	*ft_itoa(int n);

//funciones que ejecutan los builtins
//builtin_utils_o.c
int		ft_builtin(t_in *dt, int n);
int		ft_exe_echo(t_in *dt, int n);
int		ft_exe_cd(t_in *dt);
void	ft_exe_cd_aux(t_in *dt);
int		ft_exe_env(t_in *dt);
int		ft_exe_pwd(void);
int		ft_exe_exit(t_in *dt);
int		ft_exe_exit_aux(t_in *dt, long aux);
int		ft_exe_export(t_in *dt);
int		*ft_get_var_name(char *str);
int		ft_ch_name(char *str, char c);
int		ft_exe_unset(t_in *dt);

//funciones de recogida del env
//env_utils_0.c
void	ft_get_env(t_in *dt, char **envp);
void	ft_env_act(t_in *dt);
char	*ft_split_env_1(char *env);
char	*ft_split_env_2(char *env);
char	**ft_cut_root(t_in *dt);
char	**ft_add_line(t_in *dt, char **rootold);
int		ft_add_line_aux(t_in *dt);
int		ft_ch_name_exist(t_in *dt, char *str);
int		ft_ch_name_exist_bis(t_in *dt, char *str);
void	ft_change_value(t_in *dt, char *name, char *str);
char	**ft_update_env_plus(t_in *dt, char *str);
char	**ft_update_env_minus(t_in *dt, char *str);
char	**ft_update_env_aux(t_in *dt, char c);
int		ft_update_env_aux_aux(t_in *dt, char c);

//funciones de ejecucion del minishel, las que lanzan el programa
//exe_utils_0.c
int		ft_exec(t_in *dt);
void	ft_exec_aux(int i, t_in *dt);
void	ft_clean(t_in *dt);
int		ft_ch_buil(char *name, t_list *list);
int		ft_ch_cmde(t_in *dt);
int		ft_ch_cmde_aux(t_in *dt);
void	ft_ch_cmde_aux_aux(t_in *dt);
int		ft_execve(t_in *dt, int n);
int		ft_exe_cmd(t_in *dt, int n);
int		ft_exe_cmd_builtin(t_in *dt, int n);
int		ft_exe_cmd_exe(t_in *dt, int n);
int		ft_exe_cmd_builtin_st(t_in *dt, int n);
int		ft_exe_cmd_builtin_int(t_in *dt, int n);
int		ft_exe_cmd_builtin_end(t_in *dt, int n);
int		ft_builtin_fork(t_in *dt, int n);
int		ft_exe_cmd_builtin_st_aux(t_in *dt, int n);
void	ft_exe_cmd_builtin_st_aux_aux(t_in *dt, int fd0, int fd1, int pid);
int		ft_exe_cmd_exe_st(t_in *dt);
void	ft_exe_cmd_exe_st_aux(t_in *dt, int fd1);
int		ft_exe_cmd_exe_int(t_in *dt);
void	ft_exe_cmd_exe_int_aux(t_in *dt, int fd1);
int		ft_exe_cmd_exe_end(t_in *dt);
void	ft_exe_cmd_exe_end_aux(t_in *dt);

//funciones de liberacion de memoria
//free_utils_0.c
void	ft_free_0(t_in *dt);
void	ft_free_1(t_in *dt);
void	ft_free(t_in *dt, int i);
void	ft_free_all(t_in *dt, char *line);

//funciones que realizan el here dock (HD)
//here_doc_0.c
int		ft_ch_hd(t_in *dt, int n);
void	ft_exe_null_hd(char *str);
int		ft_exe_hd(char *str, int fdint, char **env);

//funciones de linked list
//linked_list.c
t_list	*ft_new_nod_pi(char *data, t_list **list);
t_list	*ft_new_nod_re(char *data, t_list **list, int id, char type);
t_list	*ft_new_nod_cmd(char *data, t_list **list, int id);
void	ft_add_nod_back(t_in *dt, char *data, char type, int id);
void	ft_add_nod_back_pipe(t_in *dt, char *data);
void	ft_add_nod_back_re(t_in *dt, char *data, int id, char type);
void	ft_add_nod_back_cmd(t_in *dt, char *data, int id);
void	ft_print_list_pipe(t_list **list);
void	ft_print_list_cmd(t_list **list);
void	ft_print_list_redir(t_list **list);
void	ft_add_nod_front(t_list **list, char *data);
void	ft_clean_list_pipe(t_list **list);
void	ft_clean_list_cmd(t_list **list);
void	ft_clean_list_redir(t_list **list);

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
int		ft_char_counter(char *line, char c);
char	*ft_check_env(char *line);
int		ft_check_pipe(char *line, int i);
int		ft_init(char *line, int i);
int		ft_check_in_env_list(char *env, t_in *dt);
int		ft_create_new(char *line, int z, int i, t_in *dt);
int		ft_check_quot(char *line, int i, char type);
char	*ft_replace_in_line(char *line, char *old, char *new);
char	*ft_replace_if_env(char *line, int c[2], char *new, char *result);
int		ft_pipes_list(char *line, t_in *dt, int i, int z);
int		ft_check_quotations(char *line, int i);
void	ft_div_in_lists(t_in *dt);
int		ft_check_and_create(char *line, t_in *dt, int id, char type);
char	ft_redir_type(char *line, int i);
int		ft_check_redir_1(char *line, int i);
int		ft_check_redir_2(char *line, int i);
int		ft_check_redir_3(char *line, int i);
void	ft_print_all_lists(t_in *dt);
int		ft_del_spaces(char *line, int c);
int		ft_check_create0(char *line, int c, char type);
int		ft_check_create1(char *line, int c);
int		ft_check_create3(char *line, int c[2], int id, t_in *dt);
int		ft_check_create4(t_in *dt, int bool, char *data);
int		ft_check_if39(char *line, int i); //Check if has '
char	*ft_check_if_env(char *line, int i);

//funciones para gestionar las redirecciones
//red_utils_0.c
int		ft_ch_redir(t_in *dt, int n);
void	ft_ch_redir_aux0(t_list *red, t_cr *cr);
int		ft_exe_redir(t_in *dt, int n);
int		ft_exe_redir_int(t_in *dt, int n);
int		ft_exe_redir_int_aux_1(t_in *dt, int n);
int		ft_exe_redir_int_aux_2(t_in *dt);
int		ft_exe_redir_out(t_in *dt, int n);
int		ft_exe_redir_out_aux0(t_in *dt);
void	ft_redir_null(t_in *dt);

//funciones para las señales
//signal_utils_0.c
void	ft_signal(void);
void	signal_c(int signum);
void	signal_b(int signum);

#endif
