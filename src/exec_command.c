/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:26:51 by conoel            #+#    #+#             */
/*   Updated: 2019/04/26 22:54:37 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin	g_builtins[] =
{
	{PWD, &pwd_handler},
	{CD, &cd_handler},
	{ECHO, &echo_handler},
	{ENV, &env_handler},
//	{SETENV, &setenv_handler},
//	{UNSETENV, &unsetenv_handler},
	{EXIT, &exit_handler},
	{CLEAR, &clear_handler},
	{STOP, NULL}
};

int		exec_command(t_token *command)
{
	int		i;

	i = 0;
	if (!command)
		return (1);
	if (command->type == STRING)
	{
		//if (Check_path_fonction(command)))  A CODER MDR
		//	return (1);
		return (0);
	}
	while (g_builtins[i].type != STOP)
	{
		if (command->type == g_builtins[i].type)
		{
			if (!(g_builtins[i].function(command->next)))
				ft_printf("Exec error...\n");
			if (check_semilicon(command))
				return (exec_command(check_semilicon(command)));
			return (1);
		}
		i++;
	}
	return (0);
}