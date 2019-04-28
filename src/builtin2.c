/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:35:52 by conoel            #+#    #+#             */
/*   Updated: 2019/04/28 16:28:28 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		setenv_handler(t_token *command)
{
	if (!command || command->type == SEMILICON)
	{
		ft_printf("Usage : setenv var [value]\n");
		return (0);
	}
	if (command->next && command->next->next && command->next->next->type != SEMILICON)
	{
		ft_printf("setenv: too many arguments\n");
		return (0);
	}
	else if (!command->next || command->next->type == SEMILICON)
		setenv(command->content, "", 1);
	else
		setenv(command->content, command->next->content, 1);
	return (1);
}

int		unsetenv_handler(t_token *command)
{
	if (!command || command->type == SEMILICON)
		ft_printf("Usage : unsetenv var\n");
	else
		unsetenv(command->content);
	return (1);
}
