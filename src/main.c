/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:28:05 by conoel            #+#    #+#             */
/*   Updated: 2019/04/26 20:11:18 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tokens(t_token *instruction)
{
	while (instruction->next)
	{
		ft_printf("<%s [%d]> ", instruction->next->content, instruction->next->type);
		instruction = instruction->next;
	}
}

int		main(void)
{
	char	*line;
	t_token *instruction;

	while (1)
	{
		ft_printf("\n$> ");
		line = get_the_file(0);
		instruction = lexer(line);
		print_tokens(instruction);
		release_tokens(instruction);
	}
	return (0);
}