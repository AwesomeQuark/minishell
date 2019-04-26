/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:28:10 by conoel            #+#    #+#             */
/*   Updated: 2019/04/26 15:38:04 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

int				add_token(char *content, size_t size, t_token_type type, t_token *head)
{
	t_token	*new;
	t_token	*last;

	if (!(new = malloc_garbage(sizeof(t_token))))
		return (0);
	new->content = ft_memdup(content, size);
	new->size = size;
	new->type = type;
	new->next = NULL;
	if (!(last = last_token(head)))
		return (0);
	last->next = new;
	return (1);
}
