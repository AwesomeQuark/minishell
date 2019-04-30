/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:52:03 by conoel            #+#    #+#             */
/*   Updated: 2019/04/30 19:24:03 by conoel           ###   ########.fr       */
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

static void			skip_until_char(char **file, char **last_token, char c)
{
	*last_token += 1;
	*file += 1;
	while (**file != '\0' && **file != c)
		*file += 1;
}

static int			handle_escape(t_token *head, char **file,
	char **last_token)
{
	if (**file == ' ' || **file == '\t' || **file == '\n')
	{
		if (*last_token != *file)
			add_token(*last_token, *file - *last_token, STRING, head);
		*file += 1;
		*last_token = *file;
		return (1);
	}
	if (**file == '"')
		skip_until_char(file, last_token, '\"');
	else if (**file == '\'')
		skip_until_char(file, last_token, '\'');
	else
		return (0);
	if (*last_token != *file)
		add_token(*last_token, *file - *last_token, STRING_RAW, head);
	*file += 1;
	*last_token = *file;
	return (1);
}

static t_token_def	*search_token_type(char **file, char **last_token, t_token *head)
{
	size_t	i;

	i = 0;
	while (g_tokens[i].type != STOP)
	{
		if (ft_strncmp(*file, g_tokens[i].content, g_tokens[i].size) == 0
			&& ((*file)[g_tokens[i].size] == ' ' || (*file)[g_tokens[i].size] == '\n'
			|| (*file)[g_tokens[i].size] == ';') && *last_token == *file)
			return (&g_tokens[i]);
		i++;
	}
	if (**file == ';')
	{
		if (*last_token != *file)
			add_token(*last_token, *file - *last_token, STRING, head);
		add_token(*file, 1, SEMILICON, head);
		*file += 1;
		*last_token = *file;
		return (search_token_type(file, last_token, head));
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
		if (handle_escape(head, &file, &last_token_found))
			continue ;
		if (!(current = search_token_type(&file, &last_token_found, head)))
		{
			file++;
			continue ;
		}
		if (last_token_found != file)
			add_token(last_token_found, file - last_token_found, STRING, head);
		file += current->size;
		last_token_found = file;
		if (!(add_token(current->content, current->size, current->type, head)))
			return (0);
	}
	if (last_token_found != file && !(file - last_token_found == 1 && *last_token_found == '\n'))
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
	replace_links(head);
	return (head);
}
