/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 16:35:44 by mmoullec          #+#    #+#             */
/*   Updated: 2016/05/09 16:06:59 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *d, const void *s, size_t n)
{
	char		*dest;
	const char	*src;
	size_t		i;

	i = 0;
	dest = (char*)d;
	src = (char*)s;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (d);
}
