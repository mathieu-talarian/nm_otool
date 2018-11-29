/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 15:45:33 by mmoullec          #+#    #+#             */
/*   Updated: 2016/05/09 17:32:03 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_pos(char *buf, int nb)
{
	int i;

	i = 0;
	while (nb != 0)
	{
		buf[i] = (nb % 10) + '0';
		nb = nb / 10;
		i++;
	}
	buf[i] = 0;
	return (buf);
}

static char		*ft_neg(char *buf, int nb)
{
	int i;

	i = 0;
	while (nb != 0)
	{
		buf[i] = (nb % 10) * -1 + '0';
		nb = nb / 10;
		i++;
	}
	buf[i] = '-';
	i++;
	buf[i] = 0;
	return (buf);
}

static int		ft_nb_size(int nb)
{
	int i;

	i = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int nb)
{
	char	*buf;
	int		i;

	i = 0;
	if (!(buf = (char *)malloc(sizeof(buf) * (ft_nb_size(nb) + 1))))
		return (NULL);
	if (nb == 0)
		*buf = '0';
	if (nb > 0)
		buf = ft_pos(buf, nb);
	if (nb < 0)
		buf = ft_neg(buf, nb);
	ft_strrev(buf);
	return (buf);
}
