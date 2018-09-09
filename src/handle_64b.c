#include "ft_nm.h"

static void init_h(t_h64 *h, char *ptr)
{
    h->header = (struct mach_header_64 *)ptr;
    h->ncmds = h->header->ncmds;
    h->lc = (void *)ptr + sizeof(struct mach_header_64);
    h->list = NULL;
    h->sec = NULL;
}

static t_h64 _t(t_h64 *h, char *ptr, struct symtab_command *l)
{
    h->sym = l;
    h->stringtable = (void *)ptr + l->stroff;
    h->el = (void *)ptr + l->symoff;
    return *h;
}

void new_sector(t_sectors *s, char *sectname, int i)
{
    s->name = ft_strdup(sectname);
    s->nb = i;
}

void new_segs(t_list **sec, struct load_command *lc)
{
    int i;
    t_sectors sector;
    struct section_64 *s;
    struct segment_command_64 *seg;

    i = -1;
    seg = (struct segment_command_64 *)lc;
    s = (struct section_64 *)(seg + sizeof(seg) / sizeof(void *));
    while (++i < seg->nsects)
    {
        new_sector(&sector, s->sectname, i);
        ft_lstadd(sec, ft_lstnew(&sector, sizeof(t_sectors)));
        s = (struct section_64 *)(((void *)s) + sizeof(struct section_64));
        i++;
    }
}

void section(t_h64 *h)
{
    struct load_command *lc;
    int i;

    i = -1;
    lc = h->lc;
    while (++i < h->ncmds)
    {
        if (lc->cmd == LC_SEGMENT_64)
            new_segs(&h->sec, lc);
        lc += lc->cmdsize / sizeof(void *);
    }
}

int handle_64(char *ptr)
{
    int i;
    t_h64 h;

    i = -1;
    init_h(&h, ptr);
    section(&h);
    while (++i < h.ncmds)
    {
        if (h.lc->cmd == LC_SYMTAB)
            return handle_output(_t(&h, ptr, (struct symtab_command *)h.lc));
        h.lc = (void *)h.lc + h.lc->cmdsize;
    }
    return EXIT_FAILURE;
}