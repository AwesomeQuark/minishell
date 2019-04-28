/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 17:59:02 by conoel            #+#    #+#             */
/*   Updated: 2019/04/28 18:36:56 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		replace_tilde(t_token *current)
{
	char	*new;
	size_t	i;

	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '~')
		{
			current->content[i] = 0;
			new = concat(current->content, get_env("HOME="), &current->content[i + 1]);
			free(current->content);
			current->content = new;
		}
		i++;
	}
}

static void		replace_dollar(t_token *current)
{
	char	*new;
	char	*var;
	size_t	i;
	size_t	var_size;

	i = 0;
	var_size = 0;
	while (current->content[i])
	{
		if (current->content[i] == '$')
		{
			current->content[i] = '\0';
			i++;
			while (current->content[i + var_size] && current->content[i + var_size] != '$')
				var_size++;
			if (!(var = ft_memdup(&current->content[i], var_size + 2)))
				return ;
			var[var_size] = '=';
			var[var_size + 1] = '\0';
			new = concat(current->content, get_env(var), &current->content[i + var_size]);
			free(current->content);
			free(var);
			current->content = new;
			i = 0;
		}
		i++;
	}
}

void			replace_links(t_token *head)
{
	while (head)
	{
		if (head->type == STRING)
		{
			replace_tilde(head);
			replace_dollar(head);
		}
		head = head->next;
	}
}