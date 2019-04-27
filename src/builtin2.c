/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:35:52 by conoel            #+#    #+#             */
/*   Updated: 2019/04/27 12:59:36 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		clear_handler(t_token *command)
{
	struct winsize	w;

	command = (t_token *)command;
	ioctl(0, TIOCGWINSZ, &w);
	while (w.ws_row--)
		ft_printf("\n");
	ft_printf("\033[0;0H");
	return (1);
}
