/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 15:23:41 by mmoullec          #+#    #+#             */
/*   Updated: 2016/04/07 12:36:16 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*des;
	int		i;

	i = 0;
	des = NULL;
	if (s && f && s[0] != 0)
	{
		if ((des = (char *)malloc(sizeof(*des) * ft_strlen(s) + 1)))
		{
			while (i < (int)ft_strlen(s))
			{
				des[i] = (*f)(s[i]);
				i++;
			}
			des[i] = '\0';
			return ((char *)des);
		}
	}
	return (NULL);
}
