/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:16:46 by conoel            #+#    #+#             */
/*   Updated: 2019/04/28 16:38:49 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *var)
{
	size_t	i;

	i = 0;
	while (environ[i])
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

