/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 18:52:00 by mmoullec          #+#    #+#             */
/*   Updated: 2016/04/04 20:50:37 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *baby, size_t len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (baby[i] == 0)
		return ((char *)src);
	if (src[j] == 0 || len == 0)
		return (NULL);
	while (src[i] && i < (int)len)
	{
		j = 0;
		if (src[i + j] == baby[j])
		{
			while ((src[i + j] == baby[j]) && baby[j] && (i + j < (int)len))
				j++;
			if (j == (int)ft_strlen(baby))
				return ((char *)(&src[i]));
		}
		i++;
	}
	return (0);
}
