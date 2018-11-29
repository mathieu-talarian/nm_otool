/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 18:24:16 by mmoullec          #+#    #+#             */
/*   Updated: 2016/04/04 17:05:03 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int d, size_t n)
{
	size_t	i;
	char	*str;
	char	c;

	i = 0;
	str = (char *)s;
	c = (char)d;
	while (i < n)
	{
		if (str[i] == c)
			return ((unsigned char*)&str[i]);
		i++;
	}
	return (NULL);
}
