/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 21:05:03 by mmoullec          #+#    #+#             */
/*   Updated: 2016/05/09 17:41:20 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list *new;

	if (!(new = (t_list *)malloc(sizeof(*new))))
		return (NULL);
	else
	{
		if (!(content))
		{
			new->content = NULL;
			new->content_size = 0;
		}
		else
		{
			if (!(new->content = malloc(sizeof(content_size))))
				return (NULL);
			ft_memmove((new->content), content, content_size);
			new->content_size = content_size;
		}
		new->next = NULL;
	}
	return (new);
}
