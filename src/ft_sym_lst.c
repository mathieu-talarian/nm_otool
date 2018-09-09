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

void swap(t_sym_l *a, t_sym_l *b)
{
    if (a == b)
        return;

    a->next = b->next;
    b->previous = a->previous;

    if (a->next != NULL)
        a->next->previous = a;

    if (b->previous != NULL)
        b->previous->next = b;

    b->next = a;
    a->previous = b;
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
        if (f(l->sti, l->next->sti) > 0)
        {
            swap(l, l->next);
            sym_l_sort(symbols, f);
        }
        l = l->next;
    }
}