/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 17:24:07 by mmoullec          #+#    #+#             */
/*   Updated: 2016/05/27 19:41:16 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void				lstpushback(t_list_mem **mem, char *tmp, int fd)
{
	t_list_mem *ll;
	t_list_mem *new;

	ll = *mem;
	if (!(new = (t_list_mem *)malloc(sizeof(*new))))
		return ;
	else
	{
		new->tmp = tmp;
		new->fd = fd;
	}
	new->next = NULL;
	if (new && ll)
	{
		while (ll->next)
			ll = ll->next;
		ll->next = new;
	}
	else
	{
		if (new)
			*mem = new;
	}
}

static void				swap_str(char **tmp, char **str)
{
	char	*temp;

	temp = ft_strjoin(*tmp, *str);
	ft_strdel(tmp);
	*tmp = ft_strdup(temp);
	ft_strdel(&temp);
}

static int				test_tmp(char **tmp, char **line, int j)
{
	int		i;
	char	*chr;
	char	*temp;
	char	*str;

	if (j == 0 && (chr = ft_strchr(*tmp, '\n')))
	{
		i = chr - *tmp;
		str = ft_strsub(*tmp, 0, i);
		*line = ft_strdup(str);
		ft_strdel(&str);
		temp = ft_strsub(*tmp, i + 1, ft_strlen(*tmp) - i);
		ft_strdel(tmp);
		*tmp = ft_strdup(temp);
		ft_strdel(&temp);
		return (1);
	}
	else if (j == 1)
	{
		*line = ft_strsub(*tmp, 0, ft_strlen(*tmp));
		ft_strdel(tmp);
		return (1);
	}
	return (0);
}

static int				gnl(const int fd, char **line, char **tmp, int re)
{
	char	buf[BUFF_SIZE + 1];
	char	*str;

	if (*tmp && **tmp)
		if (test_tmp(tmp, line, 0))
			return (1);
	if ((re = read(fd, &buf, BUFF_SIZE)) > 0)
	{
		buf[re] = 0;
		str = ft_strdup(buf);
		if (!*tmp)
			*tmp = ft_strdup(str);
		else
			swap_str(tmp, &str);
		ft_strdel(&str);
		return (gnl(fd, line, tmp, re));
	}
	if (re < 0)
		return (-1);
	if (*tmp && **tmp)
		return (test_tmp(tmp, line, 1));
	return (0);
}

int						get_next_line(const int fd, char **line)
{
	static t_list_mem	*mem = NULL;
	t_list_mem			*temp;
	int					re;

	re = 0;
	temp = mem;
	if (fd < 0)
		return (-1);
	if (!temp)
	{
		lstpushback(&mem, NULL, fd);
		return (get_next_line(fd, line));
	}
	else
	{
		while (temp)
		{
			if (temp->fd == fd)
				return (gnl(temp->fd, line, &temp->tmp, re));
			temp = temp->next;
		}
		lstpushback(&mem, NULL, fd);
		return (get_next_line(fd, line));
	}
	return (-1);
}
