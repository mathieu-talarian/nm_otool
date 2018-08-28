/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 19:51:40 by mmoullec          #+#    #+#             */
/*   Updated: 2016/04/05 16:56:45 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *src, const char *baby)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (baby[i] == 0)
		return ((char *)src);
	if (src[j] == 0)
		return (NULL);
	while (src[i])
	{
		j = 0;
		if (src[i] == baby[j])
		{
			while ((src[i + j] == baby[j]) && baby[j])
				j++;
			if (j == (int)ft_strlen(baby))
				return ((char *)&src[i]);
		}
		i++;
	}
	return (0);
}
