/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:35:52 by conoel            #+#    #+#             */
/*   Updated: 2019/04/30 00:02:56 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			setenv_handler(t_token *command)
{
	if (!command || command->type == SEMILICON)
	{
		ft_printf("Usage : setenv var [value]\n");
		return (0);
	}
	if (command->next && command->next->next
		&& command->next->next->type != SEMILICON)
	{
		ft_printf("setenv: too many arguments\n");
		return (0);
	}
	if (!command->next || command->next->type == SEMILICON)
		set_env(command->content, NULL);
	else
		set_env(command->content, command->next->content);
	return (1);
}

int			unsetenv_handler(t_token *command)
{
	if (!command || command->type == SEMILICON)
	{
		ft_printf("Usage : unsetenv var\n");
		return (0);
	}
	unset_env(command->content);
	return (1);
}

static char	*cd_get_path(t_token *command)
{
	char	*path;

	if (command && command->type != SEMILICON && command->next
		&& command->next->type != SEMILICON)
	{
		ft_printf("cd: too many arguments\n");
		return ((char *)1);
	}
	if (!command || command->type == SEMILICON)
		path = ft_strdup(get_env("HOME="));
	else if (command->content[0] == '/')
		path = command->content;
	else
		path = concat(get_env("PWD="), "/", command->content);
	return (path);
}

int			cd_handler(t_token *command)
{
	char	*path;
	char	*tmp;

	tmp = NULL;
	if ((path = cd_get_path(command)) == (char *)1)
		return (0);
	if (path && access(path, F_OK) == 0)
		chdir(path);
	else if (command)
		ft_printf("cd: no such file or directory: %s\n", command->content);
	else
		ft_printf("cd: NULL directory (try setenv $HOME)\n");
	tmp = getcwd(NULL, PATH_MAX);
	set_env("PWD", tmp);
	free(path);
	free(tmp);
	if (command && path == command->content)
		command->content = NULL;
	return (1);
}
