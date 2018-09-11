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
    int type;
    char *sti;
    char *value;
} t_symbols;

typedef struct s_sec_l
{
    char *name;
    int nb;
    struct s_sec_l *next;
} t_sec_l;

typedef struct s_sym_l
{
    int *type;
    char *sti;
    char *value;
    struct s_sym_l *next;
    struct s_sym_l *previous;
} t_sym_l;

typedef struct s_h64
{
    int ncmds;
    struct mach_header_64 *header;
    struct load_command *lc;
    struct symtab_command *sym;

    char *stringtable;
    struct nlist_64 *el;

    void *ptr;
    off_t size;
    t_sec_l *sectors;
    t_sym_l *symbols;
} t_h64;

typedef struct s_env
{
    char *error;
    t_h64 h;
} t_env;

typedef int (*HandleFunc)(t_env e, char *ptr, off_t size);

HandleFunc handle_func(char *ptr);

int ft_nm(int ac, char **av);

int handle_64(t_env e, char *ptr, off_t size);

int handle_output(t_h64 h);

char type(t_sec_l **sec, uint8_t type, int v, uint8_t n_sect);

void sec_l_add(t_sec_l **sectors, t_sec_l *new);
void sec_l_del(t_sec_l **sectors);

void sym_l_add(t_sym_l **symbols, t_sym_l *new);
void sym_l_del(t_sym_l **symbols);
void sym_l_sort(t_sym_l **symbols, int (*f)(char *el1, char *el2));
int sl(char *el1, char *el2);

char *value_to_add(uint64_t value);

int is_corrupted(unsigned char *ptr, void *file, off_t size);

#endif