#include "ft_nm.h"

void sec_l_add(t_sec_l **sectors, t_sec_l *new)
{
    if (new)
    {
        new->next = *sectors;
        *sectors = new;
    }
}

void sec_l_del(t_sec_l **sectors)
{
    t_sec_l *l;
    t_sec_l *n;

    l = *sectors;
    while (l)
    {
        n = l->next;
        ft_strdel(&l->name);
        ft_strdel((char **)&l);
        l = n;
    }
    *sectors = NULL;
}