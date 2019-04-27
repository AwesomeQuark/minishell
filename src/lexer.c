/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:52:03 by conoel            #+#    #+#             */
/*   Updated: 2019/04/27 12:55:45 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token_def	g_tokens[] =
{
	{";", 1, SEMILICON},
	{"pwd", 3, PWD},
	{"cd", 2, CD},
	{"echo", 4, ECHO},
	{"env", 3, ENV},
	{"setenv", 6, SETENV},
	{"unsetenv", 8, UNSETENV},
	{"exit", 4, EXIT},
	{"clear", 4, CLEAR},
	{NULL, 0, STOP}
};

static int			handle_escape(char **file, char **last_token_found)
{
	if (**file == ' ' || **file == '\t' || **file == '\n')
		return (1);
	if (**file == '"')
	{
		*last_token_found += 1;
		*file += 1;
		while (**file != '"')
			*file += 1;
		return (1);
	}
	return (0);
}

static t_token_def	*search_token_type(char *file)
{
	size_t	i;

	i = 0;
	while (g_tokens[i].type != STOP)
	{
		if (ft_strncmp(file, g_tokens[i].content, g_tokens[i].size) == 0)
			return (&g_tokens[i]);
		i++;
	}
	return (NULL);
}

int					lexer_main_loop(char *file, t_token *head)
{
	t_token_def	*current;
	char		*last_token_found;

	last_token_found = file;
	while (file && *file)
	{
		if (handle_escape(&file, &last_token_found))
		{
			if (last_token_found != file)
				add_token(last_token_found, file - last_token_found, STRING,
					head);
			file++;
			last_token_found = file;
			continue ;
		}
		if (!(current = search_token_type(file)))
		{
			file++;
			continue ;
		}
		if (last_token_found != file && head->next != NULL)
			add_token(last_token_found, file - last_token_found, STRING, head);
		file += current->size;
		last_token_found = file;
		if (!(add_token(current->content, current->size, current->type, head)))
			return (0);
	}
	if (last_token_found != file)
		add_token(last_token_found, file - last_token_found, STRING, head);
	return (1);
}

t_token				*lexer(char *line)
{
	t_token	*head;

	if (!(head = malloc(sizeof(t_token))))
		return (NULL);
	head->type = START;
	head->next = NULL;
	head->size = 0;
	head->content = NULL;
	lexer_main_loop(line, head);
	return (head);
}
