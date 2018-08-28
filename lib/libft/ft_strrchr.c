/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 17:40:41 by mmoullec          #+#    #+#             */
/*   Updated: 2016/05/09 14:33:16 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *src, int c)
{
	int i;

	if (src)
	{
		i = ft_strlen(src);
		if (c == 0)
			return ((char *)&src[i]);
		while (i >= 0)
		{
			if (src[i] == c)
				return ((char *)&src[i]);
			i--;
		}
	}
	return (0);
}
