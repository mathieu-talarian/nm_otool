#include "ft_nm.h"

void init_h_64(t_h64 *h, char *ptr, off_t size, char opt)
{
    h->header = (struct mach_header_64 *) ptr;
    h->nb_cmds = swap_test(h->header->ncmds, opt);
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
    if (is_corrupted((unsigned char *) (lc + 1), h->ptr, h->size) || (lc->cmdsize % 8))
        return EXIT_FAILURE;
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
    printf("%s\n", err);
    // e->error = ft_strdup(err);
    return EXIT_FAILURE;
}

void match_sectors(char *segname, char *secname, t_env *e, uint64_t j)
{
}

int sect_64(struct segment_command_64 *segment_command_64, t_env *e)
{
    struct section_64 *section_64;
    char *             segname;
    char *             sectname;
    uint64_t           j;
    uint64_t           ncmds;

    section_64 = (void *) segment_command_64 + sizeof(segment_command_64);
    j = -1;
    ncmds = (e->opt & TO_SWAP) ? SwapInt(segment_command_64->nsects) :
                                 segment_command_64->nsects;
    while (++j < ncmds)
    {
        sectname = section_64[j].sectname;
        segname = section_64[j].segname;
        match_sectors(segname, sectname, e, j);
    }
    return EXIT_SUCCESS;
}

int handle_lc_64(t_env *e, char *ptr)
{
    if (e->h.lc.cmd == LC_SEGMENT_64)
        sect_64((struct segment_command_64 *) e->h.load_command, e);
    if (e->h.lc.cmd == LC_SYMTAB)
        ;
    // symtab_64((struct symtab_command *) e->load_command, e);
    return EXIT_SUCCESS;
}

int handle_64(t_env *e, char *ptr)
{
    int i;

    i = -1;
    init_h_64(&e->h, ptr, e->filesize, e->opt);
    // if (is_corrupted((unsigned char *) (e->h.header + 1), (void *) ptr, e->filesize))
    //     return err(e, "The file is corrupted at macheader64");
    // if (section(&e->h))
    //     return err(e, "The file is corrupted at LC_SEGMENT_64");
    while (++i < e->h.nb_cmds)
    {
        e->h.lc = (e->opt & TO_SWAP) ? SwapInt(e->h.load_command->cmd) :
                                       e->h.load_command->cmd;
        if (is_corrupted(e->filesize, (long) ptr,
                         (long) ((void *) e->load_command + e->lc.cmdsize)))
            return ft_putendl_fd_int("File Corrupted", 2, EXIT_FAILURE);
        if (handle_lc_64(e, ptr))
            return EXIT_FAILURE;
        if (e->h.lc->cmd == LC_SYMTAB)
            return handle_output(_t(&e->h, ptr, (struct symtab_command *) e->h.lc));
        e->h.lc = (void *) e->h.lc + e->h.lc->cmdsize;
    }
    return EXIT_FAILURE;
}
