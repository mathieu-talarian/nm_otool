#include "ft_nm.h"

static int get_length(long unsigned int n)
{
    int length;

    length = (n == 0) ? 1 : 0;
    while (n != 0)
    {
        n = n / 16;
        length++;
    }
    return (length);
}

static void norme_loop(char *str, long unsigned int *n, int *length)
{
    while ((*n) != 0)
    {
        if ((*n) % 16 > 9)
            str[(*length)] = (*n) % 16 + 'a' - 10;
        else
            str[(*length)] = (*n) % 16 + '0';
        (*n) = (*n) / 16;
        (*length)--;
    }
}

char *ft_xlongtoa(long unsigned int n)
{
    char *str;
    int   length;

    length = get_length(n);
    str = NULL;
    str = (char *) malloc(sizeof(char) * (length + 1));
    if (str)
    {
        str[length] = '\0';
        length--;
        str[length] = '0';
        norme_loop(str, &n, &length);
    }
    return str;
}

void pl(t_sym_l **s)
{
    t_sym_l *l;

    l = *s;
    while (l)
    {
        ft_putstr(l->value);
        ft_putchar(' ');
        ft_putchar(l->type);
        ft_putchar(' ');
        ft_putstr(l->sti);
        ft_putchar('\n');
        l = l->next;
    }
}

int handle_output(t_sym_l *sym)
{
    sym_l_sort(&sym, sl);
    pl(&sym);
    sym_l_del(&sym);
    return EXIT_SUCCESS;
}