/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 14:09:48 by mmoullec          #+#    #+#             */
/*   Updated: 2016/04/05 18:45:23 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, unsigned int num)
{
	unsigned int i;

	i = 0;
	while (src[i] && i < num)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < num)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}
