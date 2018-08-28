/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 18:51:32 by mmoullec          #+#    #+#             */
/*   Updated: 2016/03/19 20:00:39 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int y, size_t n)
{
	char *d;
	char *s;
	char c;

	c = (char)y;
	if (n)
	{
		d = (char *)dest;
		s = (char *)src;
		c = (char)y;
		while (n != 0)
		{
			if ((*d++ = *s++) == c)
				return (d);
			n--;
		}
	}
	return (NULL);
}
