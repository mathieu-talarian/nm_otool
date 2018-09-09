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

char comp_sect(t_sectors *s)
{
    if (!ft_strcmp(s->name, SECT_DATA))
        return ('D');
    else if (!ft_strcmp(s->name, SECT_BSS))
        return ('B');
    else if (!ft_strcmp(s->name, SECT_TEXT))
        return ('T');
    return ('S');
}

char sectorize(t_list **sect, uint8_t n_sect)
{
    t_list *l;
    t_sectors *s;

    l = *sect;
    while (l)
    {
        s = (t_sectors *)l->content;
        if ((s->nb) == n_sect)
            return (comp_sect(s));
        l = l->next;
    }
    return 'T';
}

char type(t_list **sec, uint8_t type, int v, uint8_t n_sect)
{
    uint8_t t;
    char r;

    t = type & N_TYPE;
    r = '?';
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