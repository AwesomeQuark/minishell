/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:51:24 by conoel            #+#    #+#             */
/*   Updated: 2019/04/29 22:31:44 by conoel           ###   ########.fr       */
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

	i = 0;
	size = tab_size(tab);
	if (!(ret = malloc(sizeof(char *) * size)))
		return (0);
	ft_bzero(ret, size + 1);
	size = 0;
	while (ret[size])
	{
		if (size == index)
			i++;
		ret[size] = ft_strdup(tab[i]);
		size++;
		i++;
	}
	free_tab(tab);
	return (ret);
}

char			**realloc_tab_add_var(char **tab, char *new)
{
	char	**ret;
	size_t	size;

	size = tab_size(tab);
	if (!(ret = malloc(sizeof(char *) * (size + 2))))
		return (NULL);
	ret[size + 1] = NULL;
	size = 0;
	while (tab[size])
	{
		ret[size] = ft_strdup(tab[size]);
		size++;
	}
	ret[size] = new;
	free_tab(tab);
	return (ret);
}

char			**copy_tab(char **tab)
{
	char	**ret;
	size_t	size;

	size = tab_size(tab);
	if (!(ret = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	ret[size] = NULL;
	size = 0;
	while (tab[size])
	{
		ret[size] = ft_strdup(tab[size]);
		size++;
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
	argv = malloc(sizeof(char *) * (i + 1));
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
