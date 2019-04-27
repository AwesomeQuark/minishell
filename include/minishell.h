/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:28:18 by conoel            #+#    #+#             */
/*   Updated: 2019/04/27 23:56:47 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <signal.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include "lexer.h"

extern char **environ;

typedef struct	s_builtin
{
	t_token_type	type;
	int (*function)(t_token *);
}				t_builtin;

int				exec_command(t_token *command);

/*
**	BUILTIN HANDLERS
*/
int				pwd_handler(t_token *command);
int				cd_handler(t_token *command);
int				echo_handler(t_token *command);
int				env_handler(t_token *command);
int				setenv_handler(t_token *command);
int				unsetenv_handler(t_token *command);
int				exit_handler(t_token *command);
int				clear_handler(t_token *command);

/*
**	UTILS
*/
char			*get_env(char *var);
t_token			*check_semilicon(t_token *command);
char			**allocate_args(t_token *command);

/*
**	DISPLAY
*/
void			unknown_command(t_token *command);
void			print_prompt(void);
void			sigint_catch(int signo);

#endif