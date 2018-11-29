/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 17:57:36 by mmoullec          #+#    #+#             */
/*   Updated: 2016/04/04 17:15:28 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char *s;
	char *d;

	s = (char *)src;
	d = (char *)dest;
	if (!(dest > src && src + n > dest))
		ft_memcpy(dest, src, n);
	else
		while (n--)
			d[n] = s[n];
	return (dest);
}
