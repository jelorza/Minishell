/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*       jelorza- <jelorza-@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:11:33 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/08/10 17:21:33 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exe_redir_int_aux_2(t_in *dt)
{
	dt->hd_h = dt->hd;
	if (dt->tint == 3)
	{
		while (dt->hd->next)
		{
			ft_exe_null_hd(dt->hd->data);
			dt->hd = dt->hd->next;
		}
		dt->fdint = ft_exe_hd(dt->hd->data, dt->fdint, dt->env);
		if (dt->fdint == -1)
			return (-1);
	}
	else if (dt->tint != 3 && dt->hd)
	{
		while (dt->hd)
		{
			ft_exe_null_hd(dt->hd->data);
			dt->hd = dt->hd->next;
		}
	}
	dt->hd = dt->hd_h;
	ft_destroy_list(&dt->hd);
	return (0);
}

int	ft_exe_redir_out(t_in *dt, int n)
{
	int	i;

	i = 0;
	dt->tout = 0;
	dt->fdout = -2;
	dt->l_parse_redir = dt->hd_r;
	while (dt->l_parse_redir)
	{
		if (dt->l_parse_redir->id == n && (dt->l_parse_redir->type == 2
				|| dt->l_parse_redir->type == 4))
		{
			i = ft_exe_redir_out_aux0(dt);
			if (i == -1)
				return (-1);
			else if (i == -2)
				return (-2);
		}
		dt->l_parse_redir = dt->l_parse_redir->next;
	}
	return (0);
}

int	ft_exe_redir_out_aux0(t_in *dt)
{
	dt->tout = dt->l_parse_redir->type;
	if (dt->fdout > 0)
		close (dt->fdout);
	if (dt->tout == 4)
		dt->fdout = open (dt->l_parse_redir->data, O_CREAT
				| O_EXCL | O_RDWR | O_APPEND, 0644);
	else
		dt->fdout = open (dt->l_parse_redir->data, O_CREAT
				| O_EXCL | O_RDWR | O_TRUNC, 0644);
	if (dt->fdout == -1)
	{
		if (dt->tout == 4)
			dt->fdout = open (dt->l_parse_redir->data, O_RDWR | O_APPEND, 0644);
		else
			dt->fdout = open (dt->l_parse_redir->data, O_RDWR | O_TRUNC, 0644);
	}
	if (dt->fdout == -1)
	{
		printf ("bash: syntax error near unexpected token `>>'\n");
		return (-2);
	}
	return (0);
}

void	ft_redir_null(t_in *dt)
{
	t_list	*aux;

	if (dt->l_parse_cmd)
	{
		aux = dt->l_parse_redir;
		while (aux && aux->id < dt->l_parse_cmd->id && aux)
		{
			ft_ch_redir(dt, aux->id);
			dt->l_parse_redir = dt->hd_r;
			ft_exe_redir(dt, aux->id);
			while (aux)
				aux = aux->next;
		}
	}
	else
		ft_redir_null_aux(dt);
}

void	ft_redir_null_aux(t_in *dt)
{
	t_list	*aux;

	aux = dt->l_parse_redir;
	while (dt->l_parse_redir)
	{
		dt->l_parse_redir->id = 0;
		dt->l_parse_redir = dt->l_parse_redir->next;
	}
	dt->l_parse_redir = dt->hd_r;
	while (aux)
	{
		ft_ch_redir(dt, aux->id);
		dt->l_parse_redir = dt->hd_r;
		ft_exe_redir(dt, aux->id);
		while (aux)
			aux = aux->next;
	}
}
