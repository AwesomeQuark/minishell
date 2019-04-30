/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:16:46 by conoel            #+#    #+#             */
/*   Updated: 2019/04/30 13:49:41 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env(char *var_name)
{
	char	**var;

	if (!(var = get_env_addr(var_name)))
		return ;
	environ = realloc_tab_remove_index(environ, var - environ);
	return ;
}

void	set_env(char *var_name, char *new)
{
	char	**var;
	char	*tmp;

	if (!var_name)
		return ;
	if ((var = get_env_addr(var_name)))
	{
		tmp = *var;
		*var = concat(var_name, "=", new);
		free(tmp);
	}
	else
		environ = realloc_tab_add_var(environ, concat(var_name, "=", new));
}

char	**get_env_addr(char *var)
{
	size_t	i;

	i = 0;
	while (environ && environ[i])
	{
		if (ft_strncmp(environ[i], var, ft_strlen(var)) == 0
			&& environ[i][ft_strlen(var)] == '=')
			return (environ + i);
		i++;
	}
	return (NULL);
}

char	*get_env(char *var)
{
	size_t	i;

	i = 0;
	while (environ && environ[i])
	{
		if (ft_strncmp(environ[i], var, ft_strlen(var)) == 0)
			return (environ[i] + ft_strlen(var));
		i++;
	}
	return (NULL);
}

t_token	*check_semilicon(t_token *command)
{
	while (command)
	{
		if (command->type == SEMILICON && command->next != NULL
			&& command->next->type != SEMILICON)
			return (command->next);
		command = command->next;
	}
	return (NULL);
}
