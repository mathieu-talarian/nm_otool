/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_sp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 15:54:05 by mmoullec          #+#    #+#             */
/*   Updated: 2016/05/27 19:35:07 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_sp(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (ft_isspace(str[i]))
				ft_putchar('.');
			else
				ft_putchar(str[i]);
			i++;
		}
	}
	else
		ft_putendl("(null)");
}
