#include "ft_nm.h"

struct load_command swap_lc_cmd(struct load_command *load_command)
{
    struct load_command lc;

    lc = *load_command;
    lc.cmd = SwapInt(load_command->cmd);
    lc.cmdsize = SwapInt(load_command->cmdsize);
    return lc;
}

struct symtab_command swap_symtab(struct symtab_command *symtab_command)
{
    struct symtab_command sc_clean;

    sc_clean = *symtab_command;
    sc_clean.symoff = SwapInt(symtab_command->symoff);
    sc_clean.stroff = SwapInt(symtab_command->stroff);
    sc_clean.nsyms = SwapInt(symtab_command->nsyms);
    return (sc_clean);
}

struct symtab_command swap_symtab_cmd(struct symtab_command *symtab_command, char opt)
{
    return (opt & TO_SWAP) ? swap_symtab(symtab_command) : *symtab_command;
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

static inline void prefill32(uint8_t n_type, uint32_t n_value, char **ret, int length)
{
    if ((n_type & N_TYPE) == N_PBUD || (n_type & N_TYPE) == N_UNDF)
        *ret = value_to_add(0, length);
    else
        *ret = value_to_add(n_value, length);
}

void prefill(uint8_t n_type, uint64_t n_value, char **ret, int lenght)
{
    if ((n_type & N_TYPE) == N_PBUD || (n_type & N_TYPE) == N_UNDF)
        *ret = value_to_add(0, lenght);
    else
        *ret = value_to_add(n_value, lenght);
}

void add_lst(struct nlist_64 symtab, char *strxstart, t_env *e)
{
    char *pre;
    char  value;

    if (symtab.n_type & N_STAB)
        return;
    prefill(symtab.n_type, symtab.n_value, &pre, LENGTH64);
    value = get_type_64(symtab.n_type, symtab.n_sect, e);
    sym_l_add(&e->sym_l, sym_l_new(pre, value, strxstart));
    ft_strdel(&pre);
}

void add_lst_32(struct nlist symtab, char *strxstart, t_env *e)
{
    char *pre;
    char  value;

    if (symtab.n_type & N_STAB)
        return;
    prefill(symtab.n_type, symtab.n_value, &pre, LENGTH32);
    value = get_type_64(symtab.n_type, symtab.n_sect, e);
    sym_l_add(&e->sym_l, sym_l_new(pre, value, strxstart));
    ft_strdel(&pre);
}