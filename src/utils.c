/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:16:46 by conoel            #+#    #+#             */
/*   Updated: 2019/04/26 22:47:27 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(void)
{
	size_t	i;

	i = 0;
	while (environ[i]) {
		if (ft_strncmp(environ[i], "PWD=", 4) == 0)
			return(environ[i] + 4);
		i++;
	}
	return (NULL);
}

char	*get_user(void)
{
	size_t	i;

	i = 0;
	while (environ[i]) {
		if (ft_strncmp(environ[i], "USER=", 5) == 0)
			return(environ[i] + 5);
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