/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 11:57:53 by mmoullec          #+#    #+#             */
/*   Updated: 2018/11/28 23:08:36 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void init_h_32(t_h32 *h, char *ptr, off_t size)
{
    h->header = (struct mach_header *) ptr;
    h->ncmds = h->header->ncmds;
    h->lc_p = (void *) ptr + sizeof(struct mach_header);
    h->ptr = ptr;
    h->size = size;
    h->sectors = NULL;
    h->symbols = NULL;
}

void clean(t_env *e)
{
    e->h32.lc = *e->h32.lc_p;
    e->h32.lc.cmd = SwapInt(e->h32.lc_p->cmd);
    e->h32.lc.cmdsize = SwapInt(e->h32.lc_p->cmdsize);
}

void utils_match_nsect(char *segname, char *sectname, t_env *e, int cur)
{
    if (ft_strcmp(segname, sectname) != 0)
    {
        if (!ft_strcmp(sectname, "__data"))
            e->data_sec =
    }
}

void get_n_sect_32(struct segment_command *sc, t_env *e)
{
    struct section *   sec_32;
    char *             segname;
    char *             sectname;
    long long unsigned j;

    sec_32 = (void *) sg + sizeof(struct segment_command);
    j = 0;
    while (j < swaptest((int) sg->nsects, g->opt))
    {
        sectname = sec_32[j].sectname;
        segname = sec_32[j].segname;
        utils_match_nsect(segname, sectname, e, j);
        j++;
    }
    e->n_sect += j;
    return (0);
}

int handle_lc_32(struct load_command *lc_p, struct load_command lc, t_env *e, char *ptr)
{
    if (e->h32.lc.cmd == (e->opt & IS_32 ? LC_SEGMENT : LC_SEGMENT_64))
    {
        (e->opt & IS_32) ? get_n_sect_32((struct segment_command *) lc_p, e) : get_n_sect_64((struct segment_command *) lc_p, e);
    }
    return EXIT_SUCCESS;
}

int handle_32(t_env *e, char *ptr)
{
    uint32_t i;
    uint32_t cpt;

    cpt = -1;
    i = swap_test((int) e->h.ncmds, e->opt & TO_SWAP);
    init_h_32(&e->h32, ptr, e->filesize);
    while (++cpt < i)
    {
        e->opt &TO_SWAP ? (clean(e)) : _;
        if (handle_lc_32(e, ptr))
    }
    return (0);
}
