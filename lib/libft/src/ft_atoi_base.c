/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 18:50:23 by mmoullec          #+#    #+#             */
/*   Updated: 2016/06/03 19:34:38 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_convert_base_10(char *nb, char *base)
{
	int		i;
	int		j;
	int		res;
	int		neg;

	i = 0;
	j = 0;
	res = 0;
	neg = 1;
	if (nb[i] == '-')
		neg = -1;
	if (nb[i] == '-' || nb[i] == '+')
		nb = &nb[1];
	while (nb[i])
	{
		j = 0;
		while (base[j] != nb[i])
			j++;
		res = (res * (ft_strlen(base))) + (j);
		i++;
	}
	return (res * neg);
}

int		ft_atoi_base(char *nbr, char *base_from)
{
	char	*base;
	char	*nb;
	int		res;

	base = ft_strtrim(base_from);
	nb = ft_strtrim(nbr);
	res = ft_convert_base_10(nb, base);
	ft_strdel(&base);
	ft_strdel(&nb);
	return (res);
}
