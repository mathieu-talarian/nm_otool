/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 18:49:26 by mmoullec          #+#    #+#             */
/*   Updated: 2016/06/03 19:41:46 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_convert_base_to(int nb, char *base)
{
	int		res;
	int		j;
	int		neg;
	char	*nbre;

	j = 0;
	res = 0;
	neg = 1;
	if (!(base))
		return (0);
	nbre = ft_strnew(33);
	while (nb != 0)
	{
		res = nb % ft_strlen(base);
		nb = nb / ft_strlen(base);
		nbre[j] = base[res];
		j++;
	}
	nbre[j] = 0;
	ft_strrev(nbre);
	return (nbre);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		nb10;
	char	*base;
	char	*nb_to;

	nb10 = ft_atoi_base(nbr, base_from);
	base = ft_strtrim(base_to);
	if (nb10 == 0)
		return (nb_to = "0");
	nb_to = ft_convert_base_to(nb10, base);
	ft_strdel(&base);
	return (nb_to);
}
