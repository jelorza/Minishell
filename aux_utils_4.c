/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*       jelorza- <jelorza-@student.42urduli>     +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:11:33 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/08/11 07:01:50 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_aux(char *s1, char *s2)
{
	char	*des;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	des = (char *)malloc ((ft_strlen (s1) + ft_strlen (s2)) + 1);
	if (des == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != 00)
		des[i] = s1[i];
	j = -1;
	while (s2[++j] != 00)
	{
		des[i] = s2[j];
		i++;
	}
	des[i] = 00;
	free(s1);
	free(s2);
	return (des);
}

int	ft_pipe(int *fd)
{
	int	i;

	i = pipe (fd);
	if (i == -1)
	{
		perror ("Pipe error");
		return (-1);
	}
	return (0);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork ();
	if (pid == -1)
	{
		perror ("Fork error");
		return (-1);
	}
	return (pid);
}

int	ft_close(int descr)
{
	int	i;

	i = close (descr);
	if (i == -1)
	{
		perror ("Close error");
		return (-1);
	}
	return (0);
}

int	ft_wait(int pid)
{
	int	res;
	int	st;

	res = waitpid(pid, &st, 0);
	if (res == -1)
	{
		perror ("Waitpid error");
		return (-1);
	}
	if (g_status != 130 && g_status != 131)
		g_status = WEXITSTATUS(st);
	return (0);
}
