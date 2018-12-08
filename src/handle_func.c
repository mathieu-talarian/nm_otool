/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 18:27:27 by mmoullec          #+#    #+#             */
/*   Updated: 2018/12/08 18:27:35 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int handle_error(t_env e, char *ptr, off_t size)
{
    off_t s;
    t_env d;
    char *p;

    s = size;
    d = e;
    p = ptr;
    return EXIT_FAILURE;
}


int config(void *ptr, int *opts)
{
    uint32_t magic_number;
    magic_number = *(int *) ptr;
    if (magic_number != MH_CIGAM_64 && magic_number != MH_CIGAM && magic_number != MH_MAGIC && magic_number != MH_MAGIC_64)
        return (EXIT_FAILURE);
    if (magic_number == MH_CIGAM_64 || magic_number == MH_CIGAM)
        *opts = *opts | TO_SWAP;
    else
        *opts = *opts & ~TO_SWAP;
    if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
        *opts = *opts | IS_32;
    else
        *opts = *opts & ~IS_32;
    return EXIT_SUCCESS;
}

void _init_env(t_env *e)
{
    e->sym_l = NULL;
    e->n_sect = 0;
    e->data_sec = 0;
    e->text_sec = 0;
    e->bss_sec = 0;
}

int handle_macho(t_env *e, char *ptr)
{
    _init_env(e);
    if (config(ptr, &e->opt))
        return EXIT_FAILURE;
    if (e->opt & IS_32)
        handle_32(e, ptr);
    else
        handle_64(e, ptr);
    return EXIT_FAILURE;
}

HandleFunc handle_func(int opts)
{
    if (opts & FAT)
        return handle_fat;
    else if (opts & LIB)
        return handle_lib;
    return handle_macho;
}
