/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:28:05 by conoel            #+#    #+#             */
/*   Updated: 2019/04/27 13:19:27 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unknown_command(t_token *command)
{
	ft_printf("minishell: Unknown command %s\n", command->content);
}

static void	print_prompt(void)
{
	ft_printf("%s%s%s%s %s[%s]%s > ", BOLD, CYAN, get_env("USER="), DEF, BLUE, get_env("PWD="), DEF);
}

static void	sigint_catch(int signo)
{
	ft_printf("\n\033[31m[%d]Closing minishell..\n", signo);
	exit(1);
}

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
		if (!(exec_command(command->next)))
			unknown_command(command->next);
		release_tokens(command);
	}
	return (0);
}
