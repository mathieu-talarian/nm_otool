/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 20:10:52 by mmoullec          #+#    #+#             */
/*   Updated: 2018/12/05 18:47:07 by mmoullec         ###   ########.fr       */
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

static t_h64 _t(t_h64 *h, char *ptr, struct symtab_command *l)
{
    h->sym = l;
    h->stringtable = (void *) ptr + l->stroff;
    h->el = (void *) ptr + l->symoff;
    return *h;
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

int section(t_h64 *h)
{
    struct load_command *lc;
    int                  i;

    i = -1;
    lc = h->load_command;
    // if (is_corrupted((unsigned char *) (lc + 1), h->ptr, h->size) || (lc->cmdsize % 8))
    //  return EXIT_FAILURE;
    while (++i < h->nb_cmds)
    {
        if (lc->cmd == LC_SEGMENT_64)
            new_segs(&h->sectors, lc);
        lc += lc->cmdsize / sizeof(void *);
    }
    return EXIT_SUCCESS;
}

int err(t_env *e, char *err)
{
    // e->error = ft_strdup(err);
    return EXIT_FAILURE;
}

void match_sectors(char *segname, char *sectname, t_env *e, int j)
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

static inline struct symtab_command swap_symtab(struct symtab_command *symtab_command)
{
    struct symtab_command sc_clean;

    sc_clean = *symtab_command;
    sc_clean.symoff = SwapInt(symtab_command->symoff);
    sc_clean.stroff = SwapInt(symtab_command->stroff);
    sc_clean.nsyms = SwapInt(symtab_command->nsyms);
    return (sc_clean);
}

#define N_SECT_MASK 1024

void prefill(uint8_t n_type, uint64_t n_value, char **ret)
{
    if ((n_type & N_TYPE) == N_PBUD || (n_type & N_TYPE) == N_UNDF)
        *ret = value_to_add(0);
    else
        *ret = value_to_add(n_value);
}

char get_type(int type, t_env *e, int fallback)
{
    if (type == N_SECT)
    {
        type = fallback;
        if (type == e->bss_sec)
            return ('B');
        else if (type == e->data_sec)
            return ('D');
        else if (type == e->text_sec)
            return ('T');
        else
            return ('S');
    }
    else
    {
        if (type == N_UNDF || type == N_PBUD)
            return ('U');
        if (type == N_ABS)
            return ('A');
        if (type == N_INDR)
            return ('I');
    }
    return (' ');
}

char get_type_64(uint8_t n_type, uint8_t n_sect, t_env *e)
{
    int  type;
    char ret;

    type = n_type & N_TYPE;
    ret = get_type(type, e, n_sect);
    if (!(n_type & N_EXT))
        ret = ft_tolower(ret);
    return (ret);
}

void add_lst(struct nlist_64 symtab, char *strxstart, t_env *e)
{
    int   type;
    char *pre;
    char *s;
    char  value;

    if (symtab.n_type & N_STAB)
        dprintf(2, "");
    // type = symtab.n_sect == NO_SECT ? symtab.n_type & N_TYPE : symtab.n_sect | N_SECT_MASK;
    prefill(symtab.n_type, symtab.n_value, &pre);
    value = get_type_64(symtab.n_type, symtab.n_sect, e);
    sym_l_add(&e->sym_l, sym_l_new(pre, value, strxstart));
    ft_strdel(&pre);
    // dprintf(2, "%s %c %s\n", pre, get_type_64(symtab.n_type, symtab.n_sect, e), strxstart);
}

static inline struct symtab_command swap_symtab_cmd(struct symtab_command *symtab_command, char opt)
{
    return (opt & TO_SWAP) ? swap_symtab(symtab_command) : *symtab_command;
}

static inline struct nlist_64 swap_nlist64_cmd(struct nlist_64 nlist64, char toswap)
{
    struct nlist_64 st_clean;

    st_clean = nlist64;
    st_clean.n_value = toswap ? SwapInt(nlist64.n_value) : nlist64.n_value;
    st_clean.n_un.n_strx = toswap ? SwapInt(nlist64.n_un.n_strx) : nlist64.n_un.n_strx;
    return (st_clean);
}

int symtab_64(struct symtab_command symtab_command, char *ptr, t_env *e, int j)
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
    {
        dprintf(2, "corrupted");
        return (EXIT_FAILURE);
    }
    while (++j < e->h.nsyms)
    {
        st_c = swap_nlist64_cmd(st[j], e->opt & TO_SWAP);
        if (st_c.n_un.n_strx >= e->filesize - symtab_command.stroff)
            /* IS CORRUPTED */
            return (EXIT_FAILURE);
        add_lst(st_c, stringtable + st_c.n_un.n_strx, e);
        /* if (!((g->output)[j] = do_str_64(st_c, strtbl + st_c.n_un.n_strx, *g))) */
        /*     return (ERR_MALLOC); */
    }
    return (0);
}

int handle_lc_64(t_env *e, char *ptr)
{
    static int i = 0;

    if (e->h.lc.cmd == LC_SEGMENT_64)
        sect_64((struct segment_command_64 *) e->h.load_command, e);
    if (e->h.lc.cmd == LC_SYMTAB)
        symtab_64(swap_symtab_cmd((struct symtab_command *) e->h.load_command, e->opt), ptr, e, -1);
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
                         (long) ((void *) e->h.load_command + e->h.lc.cmdsize), 0) == -1)
            return ft_putendl_fd_int("File Corrupted", 2, EXIT_FAILURE);
        if (handle_lc_64(e, ptr))
            return EXIT_FAILURE;
        e->h.load_command = (void *) e->h.load_command + e->h.lc.cmdsize;
    }
    handle_output(e->sym_l);
    return EXIT_FAILURE;
}
