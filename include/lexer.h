/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:14:29 by conoel            #+#    #+#             */
/*   Updated: 2019/05/01 16:31:43 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "haflib.h"

typedef enum		e_list
{
	START,
	SEMILICON,
	PWD,
	CD,
	ECHO,
	ENV,
	SETENV,
	UNSETENV,
	EXIT,
	STRING,
	STRING_RAW,
	STOP
}					t_token_type;

typedef struct		s_token_def
{
	char			*content;
	size_t			size;
	t_token_type	type;
}					t_token_def;

typedef struct		s_token
{
	struct s_token	*next;
	char			*content;
	size_t			size;
	t_token_type	type;
}					t_token;

t_token				*lexer(char *line);
void				release_tokens(t_token *head);
int					add_token(char *content, size_t size, t_token_type type,
	t_token *head);
void				replace_links(t_token *head);

#endif
