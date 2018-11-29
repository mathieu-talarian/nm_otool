/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 15:41:40 by mmoullec          #+#    #+#             */
/*   Updated: 2016/05/16 16:27:43 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	j;

	if (s == NULL)
		return (NULL);
	j = 0;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str)
	{
		while (len)
		{
			str[j] = s[start];
			j++;
			start++;
			len--;
		}
		str[j] = 0;
	}
	return (str);
}
