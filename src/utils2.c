/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:51:24 by conoel            #+#    #+#             */
/*   Updated: 2019/05/02 15:54:39 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	tab_size(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

char			**realloc_tab_remove_index(char **tab, size_t index)
{
	char	**ret;
	size_t	size;
	size_t	i;
	size_t	j;

	size = tab_size(tab);
	if (!(ret = malloc(sizeof(char *) * size)))
		quit();
	ret[size - 1] = NULL;
	i = 0;
	j = 0;
	while (ret && i < size - 1)
	{
		if (i == index)
			j++;
		if (!(ret[i] = ft_strdup(tab[j])))
			quit();
		i++;
		j++;
	}
	free_tab(tab);
	return (ret);
}

char			**realloc_tab_add_var(char **tab, char *new)
{
	char	**ret;
	size_t	size;
	size_t	i;

	size = tab_size(tab);
	if (!(ret = malloc(sizeof(char *) * (size + 2))))
		quit();
	ret[size + 1] = NULL;
	i = 0;
	while (tab && i < size)
	{
		if (!(ret[i] = ft_strdup(tab[i])))
			quit();
		i++;
	}
	ret[i] = new;
	free_tab(tab);
	return (ret);
}

char			**copy_tab(char **tab)
{
	char	**ret;
	size_t	size;
	size_t	i;

	size = tab_size(tab);
	if (!(ret = malloc(sizeof(char *) * (size + 1))))
		quit();
	ret[size] = NULL;
	i = 0;
	while (tab && i < size)
	{
		ret[i] = ft_strdup(tab[i]);
		i++;
	}
	return (ret);
}

char			**allocate_args(t_token *command)
{
	char	**argv;
	t_token	*ptr;
	size_t	i;

	i = 0;
	ptr = command;
	while (command && command->type != SEMILICON)
	{
		i++;
		command = command->next;
	}
	if (!(argv = malloc(sizeof(char *) * (i + 1))))
		quit();
	argv[i] = NULL;
	command = ptr;
	i = 0;
	while (command && command->type != SEMILICON)
	{
		argv[i] = command->content;
		command = command->next;
		i++;
	}
	return (argv);
}
