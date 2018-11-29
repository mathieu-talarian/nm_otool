/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_err_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 23:09:40 by mmoullec          #+#    #+#             */
/*   Updated: 2018/11/28 23:11:18 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void lst_err_add(t_list *list, char *str)
{
    char *ret = ft_strdup(str);
    ft_lstadd(&list, ft_lstnew(void *(ret), ft_strlen(ret)));
}