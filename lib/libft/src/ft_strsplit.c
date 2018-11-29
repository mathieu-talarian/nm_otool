/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 19:47:27 by mmoullec          #+#    #+#             */
/*   Updated: 2016/05/09 17:24:47 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef	int	(*t_fun) (char, char);

const char		*ft_advance(const char *s, char c, int (*f)(char, char))
{
	int i;

	i = 0;
	while (s[i] && (*f)((char)s[i], c))
		i++;
	return (&s[i]);
}

static size_t	ft_letters(const char *s, char c, int (*f)(char, char))
{
	size_t i;

	i = 0;
	while (s[i] && (!(*f)((char)s[i], c)))
		i++;
	return (i);
}

static char		**ft_null(char **tab)
{
	if (!(tab = (char **)malloc(sizeof(*tab) * 2)))
		return (0);
	tab[0] = NULL;
	return (tab);
}

static char		*ft_fill_line(char *tab, const char *s, char c,\
		int (*f)(char, char))
{
	int i;
	int j;

	j = 0;
	i = ft_letters(s, c, (*f));
	if (!(tab = (char *)malloc(sizeof(char) * i + 1)))
		return (0);
	while (j < i)
	{
		tab[j] = s[j];
		j++;
	}
	tab[j] = 0;
	return (tab);
}

char			**ft_strsplit(const char *s, char c)
{
	int		k;
	int		i;
	char	**tab;

	k = 0;
	i = 0;
	tab = NULL;
	if (!s || !c || c == 0)
		return (ft_null(tab));
	if (ft_count_words(s, c, ft_char_cmp) <= 0)
		return (ft_null(tab));
	if (!(tab = (char **)malloc(sizeof(*tab) *\
					(ft_count_words(s, c, ft_char_cmp) + 1))))
		return (0);
	while (ft_count_words(s, c, ft_char_cmp) > 0)
	{
		s = ft_advance(s, c, ft_char_cmp);
		tab[k] = ft_fill_line(tab[k], s, c, ft_char_cmp);
		if (ft_count_words(s, c, ft_char_cmp) == 1)
			break ;
		s = &s[ft_letters(s, c, ft_char_cmp)];
		k++;
	}
	tab[k + 1] = 0;
	return (tab);
}
