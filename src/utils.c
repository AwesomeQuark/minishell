/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:16:46 by conoel            #+#    #+#             */
/*   Updated: 2019/04/29 00:16:25 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(char *var_name, char* new)
{
	char	**var;

	if (!var_name)
		return ;
	var = get_env_addr(var_name);
//	if (var)
//		free(var);
	*var = concat(var_name, new, NULL);
}

char	**get_env_addr(char *var)
{
	size_t	i;

	i = 0;
	while (environ && environ[i])
	{
		if (ft_strncmp(environ[i], var, ft_strlen(var)) == 0)
			return (&environ[i]);
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
		if (command->type == SEMILICON && command->next != NULL)
			return (command->next);
		command = command->next;
	}
	return (NULL);
}

char	**allocate_args(t_token *command)
{
	char	**argv;
	t_token	*ptr;
	size_t	i;

	i = 0;
	ptr = command;
	while (command && command->type != SEMILICON)
	{
		i++;
		command = command->next;
	}
	argv = malloc(sizeof(char *) * (i + 1));
	argv[i] = NULL;
	command = ptr;
	i = 0;
	while (command && command->type != SEMILICON)
	{
		argv[i] = command->content;
		command = command->next;
		i++;
	}
	return (argv);
}

