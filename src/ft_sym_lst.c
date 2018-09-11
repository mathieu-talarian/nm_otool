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
        ft_strdel((char **)&l->type);
        ft_strdel((char **)&l);
        l = n;
    }
    *symbols = NULL;
}

int sl(char *el1, char *el2)
{
    return ft_strcmp(el1, el2);
}

void swap_i(int **ptr1, int **ptr2)
{
    int *tmp;
    tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}

void swap_c(char **str1_ptr, char **str2_ptr)
{
    char *temp = *str1_ptr;
    *str1_ptr = *str2_ptr;
    *str2_ptr = temp;
}

void swap(t_sym_l *current, t_sym_l *next)
{
    swap_c(&current->sti, &next->sti);
    swap_c(&current->value, &next->value);
    swap_i(&current->type, &next->type);
}

void sym_l_sort(t_sym_l **symbols, int (*f)(char *el1, char *el2))
{
    t_sym_l *l;

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