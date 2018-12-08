/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_sectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 22:28:12 by mmoullec          #+#    #+#             */
/*   Updated: 2018/12/08 18:26:33 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void match_sectors(char *segname, char *sectname, t_env *e, uint32_t j)
{
    if (strcasecmp(segname, sectname) == 0)
    {
        if (!ft_strcmp(sectname, "__data"))
            e->data_sec = e->n_sect + j + 1;
        else if (!ft_strcmp(sectname, "__text"))
            e->text_sec = e->n_sect + j + 1;
    }
    else if (!ft_strcmp(segname, "__DATA") && !ft_strcmp(sectname, "__bss"))
        e->bss_sec = e->n_sect + j + 1;
}