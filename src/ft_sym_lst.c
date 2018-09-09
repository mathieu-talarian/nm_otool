#include "ft_nm.h"

void sym_l_add(t_sym_l **symbols, t_sym_l *new)
{
    if (new)
    {
        new->next = *symbols;
        *symbols = new;
        new->previous = NULL;
        if (new->next)
        {
            new->next->previous = new;
        }
    }
}

void sym_l_del(t_sym_l **symbols)
{
    t_sym_l *l;
    t_sym_l *n;

    l = *symbols;
    while (l)
    {
        n = l->next;
        ft_strdel(&l->sti);
        ft_strdel(&l->value);
        ft_strdel((char **)&l);
        l = n;
    }
    *symbols = NULL;
}

int sl(char *el1, char *el2)
{
    return ft_strcmp(el1, el2);
}

void sym_l_sort(t_sym_l **symbols, int (*f)(char *el1, char *el2))
{
    printf("a ");
    t_sym_l *l;
    t_sym_l *tmp_n;
    t_sym_l *tmp_h;
    t_sym_l *tmp_p;
    int tmpt;

    l = *symbols;
    while (l && l->next)
    {
        if (f(l->sti, l->next->sti))
        {
            tmp_p = l->previous;
            tmp_h = l;
            tmp_n = l->next;
            l->next->previous = l->previous;
            l->next->next = l;
            if (l->previous)
                l->previous->next = l->next;
            l->next = tmp_n->next;
            l->previous = tmp_n;
            tmp_n->previous = l;
            sym_l_sort(symbols, f);
        }
        l = l->next;
    }
}