#include "ft_nm.h"

static void print_output(int nsyms, int symoff, int stroff, char *ptr)
{
    int i;
    char *stringtable;

    struct nlist_64 *el;

    el = (void *)ptr + symoff;
    stringtable = (void *)ptr + stroff;
    i = 0;
    while (i < nsyms)
    {
        if ((el[i].n_type & N_TYPE) == N_SECT)
        {
            printf("ok");
        }
        printf("%s\n", stringtable + el[i].n_un.n_strx);
        i++;
    }
}

static void handle_64(char *ptr)
{
    int i;
    struct mach_header_64 *header;
    int ncmds;
    struct load_command *lc;
    struct symtab_command *sym;

    header = (struct mach_header_64 *)ptr;
    ncmds = header->ncmds;
    lc = (void *)ptr + sizeof(struct mach_header_64);
    for (i = 0; i < ncmds; i++)
    {
        if (lc->cmd == LC_SYMTAB)
        {
            sym = (struct symtab_command *)lc;
            print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
            break;
        }
        lc = (void *)lc + lc->cmdsize;
    }
}

static void nm(char *ptr)
{
    int magic_number;

    magic_number = *(int *)ptr;
    if (magic_number == MH_MAGIC_64)
        handle_64(ptr);
}