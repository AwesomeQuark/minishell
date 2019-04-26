/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:45:43 by conoel            #+#    #+#             */
/*   Updated: 2019/04/19 18:12:30 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "garbage.h"

char	*ft_strdup(const char *s)
{
	int		index;
	char	*end;

	index = ft_strlen(s) + 1;
	if (!(end = (char *)malloc(sizeof(char) * (index))))
		return (0);
	while (--index >= 0)
		end[index] = s[index];
	return (end);
}
