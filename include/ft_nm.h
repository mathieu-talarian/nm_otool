/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 20:38:07 by mmoullec          #+#    #+#             */
/*   Updated: 2018/12/03 22:31:31 by mathieumo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

#include "libft.h"

#include <ar.h>
#include <fcntl.h>
#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/stab.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>

// #include <stdbool.h>

#define _ 0

#define NO_X86_64 (1 << 2)
#define LIB (1 << 3)
#define FAT (1 << 4)
#define TO_SWAP (1 << 5)
#define IS_32 (1 << 6)

#define SwapInt(x) \
    ((__uint32_t)((((__uint32_t)(x) &0xff000000) >> 24) | (((__uint32_t)(x) &0x00ff0000) >> 8) | (((__uint32_t)(x) &0x0000ff00) << 8) | (((__uint32_t)(x) &0x000000ff) << 24)))
typedef struct s_sectors
{
    char *name;
    int   nb;
} t_sectors;

typedef struct s_symbols
{
    int   type;
    char *sti;
    char *value;
} t_symbols;

typedef struct s_sec_l
{
    char *          name;
    int             nb;
    struct s_sec_l *next;
} t_sec_l;

typedef struct s_sym_l
{
    int *           type;
    char *          sti;
    char *          value;
    struct s_sym_l *next;
    struct s_sym_l *previous;
} t_sym_l;

typedef struct s_h64
{
    int                    nb_cmds;
    struct mach_header_64 *header;
    struct load_command *  load_command;
    struct load_command    lc;
    struct symtab_command *sym;
    char *                 stringtable;
    struct nlist_64 *      el;
    void *                 ptr;
    off_t                  size;
    t_sec_l *              sectors;
    t_sym_l *              symbols;
    uint32_t               nsyms;
} t_h64;

typedef struct s_h32
{
    int                    ncmds;
    struct mach_header *   header;
    struct load_command *  lc_p;
    struct load_command    lc;
    struct symtab_command *sym_p;
    struct symtab_command  sym;
    char *                 stringtable;
    struct nlist *         el;
    void *                 ptr;
    off_t                  size;
    t_sec_l *              sectors;
    t_sym_l *              symbols;
} t_h32;

typedef struct s_env
{
    t_list *           error;
    t_h64              h;
    t_h32              h32;
    off_t              filesize;
    char *             title;
    int                opt;
    long long unsigned n_sect;
} t_env;

typedef int (*HandleFunc)(t_env *e, char *ptr);

HandleFunc handle_func(int);

int ft_nm(int, char **);

int handle_32(t_env *, char *);
int handle_64(t_env *, char *);

int handle_output(t_h64);

char type(t_sec_l **sec, uint8_t type, int v, uint8_t n_sect);

void sec_l_add(t_sec_l **sectors, t_sec_l *new);
void sec_l_del(t_sec_l **sectors);

void sym_l_add(t_sym_l **symbols, t_sym_l *new);
void sym_l_del(t_sym_l **symbols);
void sym_l_sort(t_sym_l **symbols, int (*f)(char *el1, char *el2));
int  sl(char *el1, char *el2);

char *value_to_add(uint64_t value);

// int is_corrupted(off_t filesize, unsigned char *ptr, void *file, off_t size);
int is_corrupted(long, long, long, long);

int handle_fat_arch_64(t_env *, void *, uint32_t);
int handle_fat_arch(t_env *, void *, uint32_t);

int handle_32(t_env *, char *);
int handle_macho(t_env *, char *);

int swap_test(int, int);

#endif
