/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 11:57:53 by mmoullec          #+#    #+#             */
/*   Updated: 2018/12/08 09:51:08 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int sect_32(struct segment_command *segment_command, t_env *e)
{
    struct section *section;
    char *          segname;
    char *          sectname;
    uint32_t        j;
    uint32_t        ncmds;

    section = (void *) segment_command + sizeof(struct segment_command);
    j = -1;
    ncmds =
        (e->opt & TO_SWAP) ? SwapInt(segment_command->nsects) : segment_command->nsects;
    while (++j < ncmds)
    {
        sectname = section[j].sectname;
        segname = section[j].segname;
        match_sectors(segname, sectname, e, j);
    }
    e->n_sect += j;
    return EXIT_SUCCESS;
}

static inline struct nlist swap_nlist_cmd(struct nlist nlist, char toswap)
{
    struct nlist st_clean;

    st_clean = nlist;
    st_clean.n_value = toswap ? SwapInt(nlist.n_value) : nlist.n_value;
    st_clean.n_un.n_strx = toswap ? SwapInt(nlist.n_un.n_strx) : nlist.n_un.n_strx;
    return (st_clean);
}

int symtab_32(struct symtab_command symtab_command, char *ptr, t_env *e, uint32_t j)
{
    struct nlist *st;
    struct nlist  st_c;
    char *        stringtable;

    e->h32.nsyms = (int) symtab_command.nsyms;
    if (!is_corrupted(e->filesize, 0, 0, symtab_command.symoff) &&
        !is_corrupted(e->filesize, 0, 0, symtab_command.stroff))
    {
        st = (void *) ptr + symtab_command.symoff;
        stringtable = (void *) ptr + symtab_command.stroff;
    }
    else
    {
        dprintf(2, "corrupted");
        return (EXIT_FAILURE);
    }
    while (++j < e->h32.nsyms)
    {
        st_c = swap_nlist_cmd(st[j], e->opt & TO_SWAP);
        if (st_c.n_un.n_strx >= e->filesize - symtab_command.stroff)
            /* IS CORRUPTED */
            return (EXIT_FAILURE);
        add_lst_32(st_c, stringtable + st_c.n_un.n_strx, e);
    }
    return (0);
}
int handle_lc_32(t_env *e, char *ptr)
{
    if (e->h32.lc.cmd == LC_SEGMENT)
        sect_32((struct segment_command *) e->h32.load_command, e);
    if (e->h32.lc.cmd == LC_SYMTAB)
        symtab_32(swap_symtab_cmd((struct symtab_command *) e->h32.load_command, e->opt), ptr, e, -1);
    return EXIT_SUCCESS;
}

void init_h_32(t_h32 *h, char *ptr, off_t size, char opt)
{
    h->header = (struct mach_header *) ptr;
    h->nb_cmds = swap_test(h->header->ncmds, opt & TO_SWAP);
    h->load_command = (void *) ptr + sizeof(struct mach_header);
    h->ptr = ptr;
    h->size = size;
    h->sectors = NULL;
    h->symbols = NULL;
}

int handle_32(t_env *e, char *ptr)
{
    int i;

    i = -1;
    init_h_32(&e->h32, ptr, e->filesize, e->opt);
    while (++i < e->h32.nb_cmds)
    {
        e->h32.lc =
            (e->opt & TO_SWAP) ? swap_lc_cmd(e->h32.load_command) : *e->h32.load_command;
        if (is_corrupted(e->filesize, (long) ptr,
                         (long) ((void *) e->h32.load_command + e->h32.lc.cmdsize), 0))
            return ft_putendl_fd_int("File corrupted", 2, EXIT_FAILURE);
        if (handle_lc_32(e, ptr))
            return EXIT_FAILURE;
        e->h32.load_command = (void *) e->h32.load_command + e->h32.lc.cmdsize;
    }
    handle_output(e->sym_l);
    return (0);
}
