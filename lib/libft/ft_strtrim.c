/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 15:51:44 by mmoullec          #+#    #+#             */
/*   Updated: 2016/04/05 21:14:18 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_begin_str(const char *str)
{
	int i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return ((char*)&str[i]);
}

char		*ft_strtrim(const char *s)
{
	char	*des;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	s = ft_begin_str(s);
	if (!(s[i]))
		return (ft_strdup(""));
	while (s[i])
		i++;
	while ((ft_isspace(s[i - 1])))
		i--;
	if ((des = (char *)malloc(sizeof(char) * i + 1)))
	{
		while (j < i)
		{
			des[j] = s[j];
			j++;
		}
		des[j] = 0;
	}
	return (des);
}
