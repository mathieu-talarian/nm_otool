#include "ft_nm.h"

char undef_type(int v)
{
    return v ? 'C' : 'U';
}

char abs_type()
{
    return 'A';
}

char pbud_type()
{
    return 'U';
}

char comp_sect(char* name)
{
    if (!ft_strcmp(name, SECT_DATA))
        return ('D');
    else if (!ft_strcmp(name, SECT_BSS))
        return ('B');
    else if (!ft_strcmp(name, SECT_TEXT))
        return ('T');
    return ('S');
}

char sectorize(t_sec_l** sect, uint8_t n_sect)
{
    t_sec_l* l;

    l = *sect;
    while (l) {
        if ((l->nb) == n_sect)
            return (comp_sect(l->name));
        l = l->next;
    }
    return 'T';
}

char type(t_sec_l** sec, uint8_t type, int v, uint8_t n_sect)
{
    uint8_t t;
    char r;

    t = type & N_TYPE;
    if (t == N_UNDF)
        r = undef_type(v);
    else if (t == N_ABS)
        r = abs_type();
    else if (t == N_PBUD)
        r = pbud_type();
    else if (t == N_SECT)
        r = sectorize(sec, n_sect);
    else if (t == N_INDR)
        r = 'I';
    if ((type & N_STAB) != 0)
        r = 'Z';
    if ((type & N_EXT) == 0 && r != '?')
        r += 32;
    return r;
}