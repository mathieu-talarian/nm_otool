/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 18:32:08 by mmoullec          #+#    #+#             */
/*   Updated: 2016/04/05 21:16:13 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace_atoi(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' ||
			c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	ft_check_neg(const char *str)
{
	int neg;

	neg = 1;
	while (ft_isspace_atoi(str[0]))
		str = &str[1];
	if (str[0] == '-')
		neg = -1;
	if (str[0] == '+' || str[0] == '-')
		str = &str[1];
	return (neg);
}

const char	*ft_modif_str(const char *str)
{
	while (ft_isspace_atoi(str[0]))
		str = &str[1];
	if (str[0] == '+' || str[0] == '-')
		str = &str[1];
	return (str);
}

int			ft_atoi(const char *str)
{
	int i;
	int neg;
	int res;

	res = 0;
	neg = ft_check_neg(str);
	str = ft_modif_str(str);
	i = 0;
	if (neg < 0)
	{
		while ('0' <= str[i] && str[i] <= '9')
		{
			res = (res * 10) - (str[i] - '0');
			i++;
		}
	}
	else
	{
		while ('0' <= str[i] && str[i] <= '9')
		{
			res = (res * 10) + (str[i] - '0');
			i++;
		}
	}
	return (res);
}
