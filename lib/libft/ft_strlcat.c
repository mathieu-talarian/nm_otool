/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 16:57:45 by mmoullec          #+#    #+#             */
/*   Updated: 2016/04/05 16:58:02 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict d, const char *restrict s, size_t n)
{
	size_t	des;
	size_t	src;
	int		i;

	i = 0;
	des = (size_t)ft_strlen(d);
	src = (size_t)ft_strlen(s);
	if (des > n)
		return (n + src);
	while ((s[i] != 0) && (i + des < n - 1))
	{
		d[des + i] = s[i];
		i++;
	}
	d[des + i] = 0;
	return (des + src);
}
