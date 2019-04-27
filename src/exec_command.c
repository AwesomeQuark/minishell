/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:26:51 by conoel            #+#    #+#             */
/*   Updated: 2019/04/28 00:00:31 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin	g_builtins[] =
{
	{PWD, &pwd_handler},
	{CD, &cd_handler},
	{ECHO, &echo_handler},
	{ENV, &env_handler},
	{SETENV, &setenv_handler},
	{UNSETENV, &unsetenv_handler},
	{EXIT, &exit_handler},
	{CLEAR, &clear_handler},
	{STOP, NULL}
};

static void			execute(t_token *command, char *exe_path)
{
	char	**argv;
	pid_t	pid;
	int		status;

	argv = allocate_args(command);
	if ((pid = fork()) == -1)
		return ;
	else if (pid == 0)
	{
		if (execve(exe_path, argv, environ) == -1)
			ft_printf("%m\n");
		exit(1);
	}
	wait(&status);
	free(argv);
}

static int			search_exe_in_dir(t_token *command, char *dir_name, char *exe_name)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(dir_name);
	if (!d)
		return (0);
	while ((dir = readdir(d)) != NULL)
	{
		if (ft_strcmp(dir->d_name, exe_name) == 0)
		{
			execute(command, concat(dir_name, "/", exe_name));
			return (1);
		}
	}
	closedir(d);
	return (0);
}

static int			search_exe(t_token *command)
{
	char	*path;
	char	**paths;
	size_t	i;

	i = 0;
	path = get_env("PATH=");
	paths = ft_strsplit(path, ':');
	while (paths[i])
	{
		if (search_exe_in_dir(command, paths[i], command->content))
		{
			free(paths);
			return (1);
		}
		i++;
	}
	free(paths);
	return (0);
}

int					exec_command(t_token *command)
{
	int		i;
	int		found;

	i = 0;
	found = 0;
	if (!command)
		return (1);
	if (command->type == STRING)
	{
		if (search_exe(command))
			found = 1;
	}
	else while (g_builtins[i].type != STOP)
	{
		if (command->type == g_builtins[i].type)
		{
			if (!(g_builtins[i].function(command->next)))
				ft_printf("Exec error...\n");
			found = 1;
		}
		i++;
	}
	if (!found)
		unknown_command(command);
	if (check_semilicon(command))
		return (exec_command(check_semilicon(command)));
	return (1);
}
