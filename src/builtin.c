/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:38:28 by conoel            #+#    #+#             */
/*   Updated: 2019/04/30 13:02:26 by conoel           ###   ########.fr       */
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
	command = NULL;
	free_tab(environ);
	release_tokens(g_command);
	exit(1);
}

int		env_handler(t_token *command)
{
	size_t	i;

	i = 0;
	command = (t_token *)command;
	while (environ[i])
	{
		ft_printf("%s\n", environ[i]);
		i++;
	}
	return (1);
}

int		pwd_handler(t_token *command)
{
	char *path;

	path = NULL;
	if (command && command->type != SEMILICON)
	{
		ft_printf("pwd: too many arguments\n");
		return (0);
	}
	path = getcwd(NULL, 1024);
	ft_printf("%s\n", path);
	set_env("PWD", path);
	free(path);
	return (1);
}

int		clear_handler(t_token *command)
{
	struct winsize	w;

	command = (t_token *)command;
	ioctl(0, TIOCGWINSZ, &w);
	while (w.ws_row--)
		ft_printf("\n");
	ft_printf("\033[0;0H");
	return (1);
}
