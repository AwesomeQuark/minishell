/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:16:46 by conoel            #+#    #+#             */
/*   Updated: 2019/04/27 12:21:57 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *var)
{
	size_t	i;

	i = 0;
	while (environ[i]) {
		if (ft_strncmp(environ[i], var, ft_strlen(var)) == 0)
			return(environ[i] + ft_strlen(var));
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

void	print_prompt(void)
{
	ft_printf("\n|- |%s%s%s| <> <%s%s%s>\n \\-> ", GREEN, get_env("USER="), DEF, LIGHT_GREEN, get_env("PWD="), DEF);
}
