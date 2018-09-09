#ifndef FT_NM_H
#define FT_NM_H

#include "../lib/libft/libft.h"

#include <stdio.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/stab.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

typedef struct s_sectors
{
    char *name;
    int nb;
} t_sectors;

typedef struct s_symbols
{
    char *sti;
    long int value;
    char type;
} t_symbols;

typedef struct s_h64
{
    int ncmds;
    struct mach_header_64 *header;
    struct load_command *lc;
    struct symtab_command *sym;

    char *stringtable;
    struct nlist_64 *el;

    t_list *sec;
    t_list *list;
} t_h64;

typedef int (*HandleFunc)(char *ptr);

HandleFunc handle_func(char *ptr);

int ft_nm(int ac, char **av);

int handle_64(char *ptr);

int handle_output(t_h64 h);

char type(t_list **sec, uint8_t type, int v, uint8_t n_sect);
#endif