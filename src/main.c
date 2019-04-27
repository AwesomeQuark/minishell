/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:28:05 by conoel            #+#    #+#             */
/*   Updated: 2019/04/27 23:27:06 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unknown_command(t_token *command)
{
	ft_printf("minishell: Unknown command %s\n", command->content);
}

static void	print_prompt(void)
{
	char *path;
	char *home;
	char *display;

	path = ft_strdup(get_env("PWD="));
	home = get_env("HOME=");
	if (ft_strncmp(path, home, ft_strlen(home)) == 0)
	{
		path[ft_strlen(home) - 1] = '~';
		display = &path[ft_strlen(home) - 1];
	}
	else
		display = path;
	ft_printf("%s%s%s%s %s[%s]%s > ", BOLD, CYAN, get_env("USER="), DEF, BLUE, display, DEF);
	free(path);
}

static void	sigint_catch(int signo)
{
	ft_printf("\n%s[%d]Closing minishell..%s\n", RED, signo, DEF);
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
