/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*       pojea-lo <pojea-lo@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:50:12 by jelorza-          #+#    #+#             */
/*   Updated: 2022/08/10 08:05:31 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ch_redir(t_in *dt, int n)
{
	t_cr	*cr;

	dt->fdint = -2;
	cr = (t_cr *) malloc (sizeof(t_cr));
	if (!cr)
	{
		perror ("Malloc error\n");
		return (-1);
	}
	dt->cr = cr;
	cr->i = 0;
	cr->s = 0;
	cr->ti = 0;
	cr->ts = 0;
	dt->l_parse_redir = dt->hd_r;
	while (dt->l_parse_redir)
	{
		if (dt->l_parse_redir->id == n)
			ft_ch_redir_aux0(dt->l_parse_redir, cr);
		dt->l_parse_redir = dt->l_parse_redir->next;
	}
	return (0);
}

void	ft_ch_redir_aux0(t_list *l_parse_redir, t_cr *cr)
{
	if (l_parse_redir->type == 1)
	{
		cr->i++;
		cr->ti = 1;
	}
	if (l_parse_redir->type == 3)
	{
		cr->i++;
		cr->ti = 3;
	}
	if (l_parse_redir->type == 2)
	{
		cr->s++;
		cr->ts = 2;
	}
	if (l_parse_redir->type == 4)
	{
		cr->s++;
		cr->ts = 4;
	}
}

int	ft_exe_redir(t_in *dt, int n)
{
	int	i;

	i = ft_exe_redir_int(dt, n);
	if (i == -1)
		return (-1);
	else if (i == -2)
		return (-2);
	i = ft_exe_redir_out(dt, n);
	if (i == -1)
		return (-1);
	if (i == -2)
		return (-2);
	return (0);
}

int	ft_exe_redir_int(t_in *dt, int n)
{
	int		i;

	i = 0;
	dt->tint = 0;
	dt->hd = NULL;
	dt->l_parse_redir = dt->hd_r;
	while (dt->l_parse_redir)
	{
		if (dt->l_parse_redir->id == n
			&& (dt->l_parse_redir->type == 1 || dt->l_parse_redir->type == 3))
		{
			dt->tint = dt->l_parse_redir->type;
			if (dt->l_parse_redir->type == 1)
			{
				if (ft_exe_redir_int_aux_1(dt, n) == -2)
					return (-2);
			}
			else if (dt->l_parse_redir->type == 3)
				ft_ch_hd (dt, n);
		}
		dt->l_parse_redir = dt->l_parse_redir->next;
	}
	if (ft_exe_redir_int_aux_2(dt) == -1)
		return (-1);
	return (0);
}

int	ft_exe_redir_int_aux_1(t_in *dt, int n)
{
	char	*cmdnex;

	cmdnex = NULL;
	if (dt->fdint > 0)
		close (dt->fdint);
	dt->fdint = open(dt->l_parse_redir->data, O_RDONLY);
	if (dt->fdint == -1)
	{
		cmdnex = ft_strjoin("", dt->l_parse_redir->data);
		n = -1;
		ft_ch_hd (dt, n);
		dt->hd_h = dt->hd;
		while (dt->hd)
		{
			ft_exe_null_hd(dt->hd->data);
			dt->hd = dt->hd->next;
		}
		dt->hd = dt->hd_h;
		ft_destroy_list(&dt->hd);
		printf ("bash: %s: No such file or directory\n", cmdnex);
		g_status = 1;
		free (cmdnex);
		return (-2);
	}
	return (0);
}
