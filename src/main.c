/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:28:05 by conoel            #+#    #+#             */
/*   Updated: 2019/04/28 17:26:48 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(void)
{
	char	*line;
	t_token *command;

	if (signal(SIGINT, sigint_catch) == SIG_ERR)
		ft_printf("Cannot handle signals : %m\n");
	while (1)
	{
		print_prompt();
		line = get_the_file(0);
		command = lexer(line);
		exec_command(command->next);
		//release_tokens(command);
		command= NULL;
	}
	return (1);
}
