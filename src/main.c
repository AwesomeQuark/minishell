/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:28:05 by conoel            #+#    #+#             */
/*   Updated: 2019/04/30 19:22:27 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init(void)
{
	g_pid = 0;
	environ = copy_tab(environ);
	if (signal(SIGINT, sigint_catch) == SIG_ERR)
		ft_putstr_fd("minishell: Cannot handle SIGINT...\n", 2);
	if (!get_env("PWD=") || !get_env("USER=") || !get_env("PATH="))
		ft_putstr_fd("minishell: Path / User / Pwd env unavailable\n\
			Please define them with `setenv name [value]`\n", 2);
}

void	token_print(t_token *ptr)
{
	while (ptr)
	{
		ft_printf("<%s [%d]> ", ptr->content, ptr->type);
		ptr = ptr->next;
	}
}

int			main(void)
{
	char	*line;

	init();
	while (1)
	{
		print_prompt();
		line = get_the_file(0);
		if (ft_strlen(line) == 0)
		{
			free(line);
			free_tab(environ);
			break ;
		}
		g_command = lexer(line);
		free(line);
		token_print(g_command);
		exec_command(g_command->next);
		release_tokens(g_command);
	}
	return (1);
}
