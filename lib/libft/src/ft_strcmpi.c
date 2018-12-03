/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmpi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathieumoullec <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:42:41 by mathieumo         #+#    #+#             */
/*   Updated: 2018/12/03 22:02:42 by mathieumo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmpi(const char *s1, const char *s2)
{
    const unsigned char *p1 = (const unsigned char *) s1;
    const unsigned char *p2 = (const unsigned char *) s2;
    int                  result;

    if (p1 == p2)
        return 0;
    while ((result = ft_tolower(*p1) - ft_tolower(*p2++)) == 0)
        if (*p1++ == '\0')
            break;
    return result;
}
