/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:38:28 by conoel            #+#    #+#             */
/*   Updated: 2019/04/26 22:35:06 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo_handler(t_token *command)
{
	while (command && command->type != SEMILICON)
	{
		if (command->next && command->next->type != SEMILICON)
			ft_printf("%s ", command->content);
		else
			ft_printf("%s\n", command->content);
		command = command->next;
	}
	return (1);
}

int		exit_handler(t_token *command)
{
	command = (t_token *)command;
	exit(1);
}

int		env_handler(t_token *command)
{
	size_t	i;

	i = 0;
	command = (t_token *)command;
	while(environ[i])
	{
		printf("%s\n", environ[i++]);
	}
	return (1);
}

int		pwd_handler(t_token *command)
{
	char *path;
	command = (t_token *)command;

	if (!(path = get_path()))
		return (0);
	ft_printf("%s\n", path);
	return (1);
}

int		cd_handler(t_token *command)
{
	char *path;
	size_t	i;

	i = 0;
	path = ft_strcat(get_path(), "/");
	path = ft_strcat(path, command->content);
	if (!(chdir(path)))
	{
		ft_printf("%m\n");
		return (0);
	}
	return (1);
}