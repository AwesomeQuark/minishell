/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:28:05 by conoel            #+#    #+#             */
/*   Updated: 2019/04/27 12:30:12 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unknown_command(t_token *command)
{
	ft_printf("minishell: Unknown command %s\n", command->content);
}

/*static void	print_tokens(t_token *command)
{
	while (command->next)
	{
		ft_printf("<%s [%d]> ", command->next->content, command->next->type);
		command = command->next;
	}
}*/

int		main(void)
{
	char	*line;
	t_token *command;

	if (!(signal(SIGINT, sigint_catch)))
		ft_printf("Cannot handle signals : %m\n");
	while (1)
	{
		print_prompt();
		line = get_the_file(0);
		command = lexer(line);
		//print_tokens(command);
		if (!(exec_command(command->next)))
			unknown_command(command->next);
		release_tokens(command);
	}
	return (0);
}