/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 22:08:11 by mmoullec          #+#    #+#             */
/*   Updated: 2016/04/05 22:13:53 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(const char *s, char c, int (*f)(char, char))
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (!((*f)((char)s[i], c)))
		{
			j++;
			while ((!((*f)((char)s[i], c))) && s[i])
				i++;
		}
		else
			i++;
	}
	return (j);
}
