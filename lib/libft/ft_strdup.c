/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 20:03:29 by mmoullec          #+#    #+#             */
/*   Updated: 2016/05/27 17:21:17 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*dest;

	i = 0;
	if (!(dest = (char *)malloc(sizeof(*dest) * (ft_strlen(str) + 1))))
		return (NULL);
	if (!str)
		return (NULL);
	return (ft_strcpy(dest, str));
}
