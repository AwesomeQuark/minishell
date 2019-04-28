/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:55:42 by conoel            #+#    #+#             */
/*   Updated: 2019/04/28 21:51:07 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unknown_command(t_token *command)
{
	ft_printf("minishell: Unknown command %s\n", command->content);
}

void	print_prompt(void)
{
	char *path;
	char *home;
	char *user;
	char *display;

	path = ft_strdup(get_env("PWD="));
	home = get_env("HOME=");
	user = get_env("USER=");
	if (home && path && ft_strncmp(path, home, ft_strlen(home)) == 0)
	{
		path[ft_strlen(home) - 1] = '~';
		display = &path[ft_strlen(home) - 1];
	}
	else
		display = path;
	if (user == NULL)
		user = ft_strdup("minishell");
	if (display == NULL)
		display = ft_strdup("ENV unavailable");
	if (!get_env("PATH="))
		ft_printf("\033[31m\033[1m /!\\ No PATH /!\\ ");
	ft_printf("%s%s%s %s[%s] %s->%s ", BOLD, CYAN, user, BLUE,
		display, CYAN, DEF);
	free(path);
}

void	sigint_catch(int signo)
{
	signo = 0;
	ft_printf("\n%sClosing minishell..%s\n", RED, DEF);
	exit(1);
}
