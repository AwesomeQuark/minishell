/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 17:59:02 by conoel            #+#    #+#             */
/*   Updated: 2019/04/28 22:52:48 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		replace_tilde(t_token *current, size_t *i)
{
	char	*new;

	if (current->content[*i] == '~')
	{
		current->content[*i] = 0;
		new = concat(current->content, get_env("HOME="),
			&current->content[*i + 1]);
		free(current->content);
		current->content = new;
	}
}


static void		replace_dollar(t_token *current, size_t *i)
{
	char	*new;
	char	*var;
	size_t	var_size;

	var_size = 0;
	if (current->content[*i] == '$')
	{
		current->content[*i] = '\0';
		*i += 1;
		while (current->content[*i + var_size] && current->content[*i + var_size] != '$')
			var_size++;
		if (!(var = malloc(sizeof(char) * (var_size + 2))))
			return ;
		ft_strncpy(var, &current->content[*i], var_size);
		var[var_size] = '=';
		var[var_size + 1] = '\0';
		new = concat(current->content, get_env(var), &current->content[*i + var_size]);
		free(current->content);
		free(var);
		current->content = new;
	}
}

void			replace_links(t_token *head)
{
	size_t	i;

	i = 0;
	while (head)
	{
		if (head->type == STRING)
		{
			while (head->content[i])
			{
				replace_tilde(head, &i);
				replace_dollar(head, &i);
				i++;
			}
		}
		i = 0;
		head = head->next;
	}
}
