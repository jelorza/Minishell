/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/07/26 12:15:37 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ch_hd(t_in *dt, int n)
{
	t_list	*new;

	if (n != -1)
	{
		new = ft_new(ft_strdup(dt->l_parse_redir->data), n, 0);
		ft_add_back(&dt->hd, new);
		return (0);
	}
	else
	{
		while (dt->l_parse_redir)
		{
			if (dt->l_parse_redir->type == 3)
			{
				new = ft_new(ft_strdup(dt->l_parse_redir->data), n, 0);
				ft_add_back(&dt->hd, new);
			}
			dt->l_parse_redir = dt->l_parse_redir->next;
		}
	}
	return (0);
}

void	ft_exe_null_hd(char *str)
{
	char	*line;

	g_status = -23;
	line = readline("> ");
	while (ft_compare_str(line, str) != 1 && line)
	{
		free (line);
		line = readline("> ");
	}
	free(line);
}

int	ft_exe_hd(char *str, int fdint, char **env)
{
	char	*line;

	g_status = -23;
	fdint = open (".aux_HD.txt.tmp", O_CREAT
			| O_EXCL | O_RDWR | O_APPEND, 0644);
	if (fdint == -1)
	{
		fdint = open (".aux_HD.txt.tmp", O_RDWR | O_TRUNC, 0644);
	}
	line = readline("> ");
	while (ft_compare_str(line, str) != 1 && line)
	{
		if (write (fdint, line, ft_strlen(line)) == -1)
		{
			printf ("Write error\n");
			return (-1);
		}
		free (line);
		write (fdint, "\n", 1);
		line = readline("> ");
	}
	free(line);
	close (fdint);
	fdint = open (".aux_HD.txt.tmp", O_RDONLY);
	ft_erase_aux (env);
	return (fdint);
}

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
