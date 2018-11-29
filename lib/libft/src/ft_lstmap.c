/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 18:12:11 by mmoullec          #+#    #+#             */
/*   Updated: 2016/04/05 21:04:21 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *rend;
	t_list *tmp;

	new = NULL;
	while (lst)
	{
		tmp = (*f)(lst);
		if (!(new))
		{
			new = ft_lstnew(tmp->content, tmp->content_size);
			rend = new;
			new->next = NULL;
		}
		else
		{
			new->next = ft_lstnew(tmp->content, tmp->content_size);
			new = new->next;
			new->next = NULL;
			tmp = NULL;
		}
		lst = lst->next;
	}
	return (rend);
}
