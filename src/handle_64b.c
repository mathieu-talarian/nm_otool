#include "ft_nm.h"

static void init_h(t_h64 *h, char *ptr, off_t size)
{

    h->header = (struct mach_header_64 *)ptr;
    h->ncmds = h->header->ncmds;
    h->lc = (void *)ptr + sizeof(struct mach_header_64);
    h->ptr = ptr;
    h->size = size;
    h->sectors = NULL;
    h->symbols = NULL;
}

static t_h64 _t(t_h64 *h, char *ptr, struct symtab_command *l)
{
    h->sym = l;
    h->stringtable = (void *)ptr + l->stroff;
    h->el = (void *)ptr + l->symoff;
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
    int i;
    t_sec_l *sector;
    struct section_64 *s;
    struct segment_command_64 *seg;

    i = -1;
    sector = NULL;
    seg = (struct segment_command_64 *)lc;
    s = (struct section_64 *)(seg + sizeof(seg) / sizeof(void *));
    while (++i < seg->nsects)
    {
        sector = new_sector(s->sectname, i);
        sec_l_add(sec, sector);
        s = (struct section_64 *)(((void *)s) + sizeof(struct section_64));
        i++;
    }
}

int section(t_h64 *h)
{
    struct load_command *lc;
    int i;

    i = -1;
    lc = h->lc;
    if (is_corrupted((unsigned char *)(lc + 1), h->ptr, h->size) || (lc->cmdsize % 8))
        return EXIT_FAILURE;
    while (++i < h->ncmds)
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
    e->error = ft_strdup(err);
    return EXIT_FAILURE;
}

int handle_64(t_env e, char *ptr, off_t size)
{
    int i;

    i = -1;
    init_h(&e.h, ptr, size);
    if (is_corrupted((unsigned char *)(e.h.header + 1), (void *)ptr, size))
        return err(&e, "The file is corrupted at macheader64");
    if (section(&e.h))
        return err(&e, "The file is corrupted at LC_SEGMENT_64");
    while (++i < e.h.ncmds)
    {
        if (e.h.lc->cmd == LC_SYMTAB)
            return handle_output(_t(&e.h, ptr, (struct symtab_command *)e.h.lc));
        e.h.lc = (void *)e.h.lc + e.h.lc->cmdsize;
    }
    return EXIT_FAILURE;
}