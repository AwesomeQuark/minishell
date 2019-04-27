/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:38:28 by conoel            #+#    #+#             */
/*   Updated: 2019/04/27 12:48:52 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo_handler(t_token *command)
{
	while (command && command->type != SEMILICON)
	{
		ft_printf("%s ", command->content);
		command = command->next;
	}
	write(1, "\n", 1);
	return (1);
}

int		exit_handler(t_token *command)
{
	release_tokens(command);
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

	if (command && command->type != SEMILICON)
	{
		ft_printf("pwd: too many arguments\n");
		return (0);
	}
	path = get_env("PWD=");
	ft_printf("%s\n", path);
	return (1);
}

int		cd_handler(t_token *command)
{
	char *path;
	size_t	i;

	i = 0;
	if (command && command->next && (command->next->type != SEMILICON))
	{
		ft_printf("cd: too many arguments\n");
		return (0);
	}
	if (!command || command->type == SEMILICON)
		path = get_env("HOME=");
	else if (command->content[0] == '/')
		path = command->content;
	else
	{
		path = ft_strcat(get_env("PWD="), "/");
		path = ft_strcat(path, command->content);
	}
	if (chdir(path) == -1)
	{
		ft_printf("%m\n");
		return (0);
	}
	return (1);
}