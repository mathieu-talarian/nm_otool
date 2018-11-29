/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 16:49:46 by mmoullec          #+#    #+#             */
/*   Updated: 2016/04/07 12:36:14 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*des;
	int		i;

	i = 0;
	des = NULL;
	if (s && f && s[0] != 0)
	{
		des = (char *)malloc(sizeof(*des) * ft_strlen(s) + 1);
		if (des)
		{
			while (i < (int)ft_strlen(s))
			{
				des[i] = (*f)(i, s[i]);
				i++;
			}
			des[i] = 0;
			return ((char *)des);
		}
	}
	return (NULL);
}
