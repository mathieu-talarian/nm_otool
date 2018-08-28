/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 16:04:47 by mmoullec          #+#    #+#             */
/*   Updated: 2016/04/04 21:02:18 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *str1, const char *str2)
{
	int i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
