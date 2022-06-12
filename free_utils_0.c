#include "minishell.h"

//funcion que libera los argumentos de la linea. Se usa a la salida y por si falla el malloc
void	ft_free_0(t_in *dt)
{
	int	j;

	j = -1;
	while (dt->data[++j] != NULL)
	{
		free (dt->data[j]);
		free (dt->cmd[j]);
		free (dt->rest[j]);
	}
	free (dt->data);
	free (dt->cmd);
	ft_destroy_list (dt);//libero aqui la lista y el head
	free (dt->rest);
}

void	ft_free_1(t_in *dt)
{
	int	j;

	j = -1;
	while (dt->env_name[++j] != NULL)
		free (dt->env_name[j]);
	free (dt->env_name);
	j = -1;
	while (dt->env_value[++j] != NULL)
		free (dt->env_value[j]);
	free (dt->env_value);
}

//funcion general para liberar. En función del int activa unas cosas u otras
//i = 0 - libera todo lo de la linea, NO el env (cuando salimos normal de la linea)
//i = 1 - libera todo lo de la linea y el env (cuando salimos por error del programa)
void	ft_free(t_in *dt, int i)
{
	if (i == 0 && dt->data != NULL)
		ft_free_0(dt);
	if (i == 1 && dt->env_name != NULL && dt->env_value != NULL)
		ft_free_1(dt);
}
