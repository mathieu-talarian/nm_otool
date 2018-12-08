/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 20:10:52 by mmoullec          #+#    #+#             */
/*   Updated: 2018/12/08 12:12:21 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#define ERR_IS_COMPROMISED 1

int is_corrupted(long size, long start, long jump, long offset)
{
    if (offset > size || jump - start > size)
        return (ERR_IS_COMPROMISED);
    else
        return (0);
}

void init_h_64(t_h64 *h, char *ptr, off_t size, char opt)
{
    h->header = (struct mach_header_64 *) ptr;
    h->nb_cmds = swap_test(h->header->ncmds, opt & TO_SWAP);
    h->load_command = (void *) ptr + sizeof(struct mach_header_64);
    h->ptr = ptr;
    h->size = size;
    h->sectors = NULL;
    h->symbols = NULL;
}

t_sec_l *new_sector(char *sectname, int i)
{
    t_sec_l *s;
    s = malloc(sizeof(t_sec_l));
    s->name = ft_strdup(sectname);
    s->nb = i;
    return s;
}

void new_segs(t_sec_l **sec, struct load_command *lc)
{
    uint32_t                   i;
    t_sec_l *                  sector;
    struct section_64 *        s;
    struct segment_command_64 *seg;

    i = -1;
    sector = NULL;
    seg = (struct segment_command_64 *) lc;
    s = (struct section_64 *) (seg + sizeof(seg) / sizeof(void *));
    while (++i < seg->nsects)
    {
        sector = new_sector(s->sectname, i);
        sec_l_add(sec, sector);
        s = (struct section_64 *) (((void *) s) + sizeof(struct section_64));
        i++;
    }
}

int err(t_env *e, char *err)
{
    e->error = ft_strdup(err);
    return EXIT_FAILURE;
}

int sect_64(struct segment_command_64 *segment_command_64, t_env *e)
{
    struct section_64 *section_64;
    char *             segname;
    char *             sectname;
    uint32_t           j;
    uint32_t           ncmds;

    section_64 = (void *) segment_command_64 + sizeof(struct segment_command_64);
    j = -1;
    ncmds = (e->opt & TO_SWAP) ? SwapInt(segment_command_64->nsects) :
                                 segment_command_64->nsects;
    while (++j < ncmds)
    {
        sectname = section_64[j].sectname;
        segname = section_64[j].segname;
        match_sectors(segname, sectname, e, j);
    }
    e->n_sect += j;
    return EXIT_SUCCESS;
}

#define N_SECT_MASK 1024

static inline struct nlist_64 swap_nlist64_cmd(struct nlist_64 nlist64, char toswap)
{
    struct nlist_64 st_clean;

    st_clean = nlist64;
    st_clean.n_value = toswap ? SwapInt(nlist64.n_value) : nlist64.n_value;
    st_clean.n_un.n_strx = toswap ? SwapInt(nlist64.n_un.n_strx) : nlist64.n_un.n_strx;
    return (st_clean);
}

int symtab_64(struct symtab_command symtab_command, char *ptr, t_env *e, uint32_t j)
{
    struct nlist_64 *st;
    struct nlist_64  st_c;
    char *           stringtable;

    e->h.nsyms = (int) symtab_command.nsyms;
    if (!is_corrupted(e->filesize, 0, 0, symtab_command.symoff) &&
        !is_corrupted(e->filesize, 0, 0, symtab_command.stroff))
    {
        st = (void *) ptr + symtab_command.symoff;
        stringtable = (void *) ptr + symtab_command.stroff;
    }
    else
        return ft_putendl_fd_int("Corrupted", 2, EXIT_FAILURE);
    while (++j < e->h.nsyms)
    {
        st_c = swap_nlist64_cmd(st[j], e->opt & TO_SWAP);
        if (st_c.n_un.n_strx >= e->filesize - symtab_command.stroff)
            return ft_putendl_fd_int("File corrupted", 2, EXIT_FAILURE);
        add_lst(st_c, stringtable + st_c.n_un.n_strx, e);
        /* if (!((g->output)[j] = do_str_64(st_c, strtbl + st_c.n_un.n_strx, *g))) */
        /*     return (ERR_MALLOC); */
    }
    return (0);
}

int handle_lc_64(t_env *e, char *ptr)
{
    if (e->h.lc.cmd == LC_SEGMENT_64)
        return sect_64((struct segment_command_64 *) e->h.load_command, e);
    if (e->h.lc.cmd == LC_SYMTAB)
        return symtab_64(swap_symtab_cmd((struct symtab_command *) e->h.load_command, e->opt), ptr, e, -1);
    return EXIT_SUCCESS;
}

int handle_64(t_env *e, char *ptr)
{
    int i;

    i = -1;
    init_h_64(&e->h, ptr, e->filesize, e->opt);

    while (++i < e->h.nb_cmds)
    {
        e->h.lc = (e->opt & TO_SWAP) ? swap_lc_cmd(e->h.load_command) : *e->h.load_command;
        if (is_corrupted(e->filesize, (long) ptr,
                         (long) ((void *) e->h.load_command + e->h.lc.cmdsize), 0))
            return ft_putendl_fd_int("File Corrupted", 2, EXIT_FAILURE);
        if (handle_lc_64(e, ptr))
            return EXIT_FAILURE;
        e->h.load_command = (void *) e->h.load_command + e->h.lc.cmdsize;
    }
    handle_output(e->sym_l);
    return EXIT_SUCCESS;
}
