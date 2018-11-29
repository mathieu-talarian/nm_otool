#include "ft_nm.h"

static int get_length(long unsigned int n)
{
    int length;

    length = (n == 0) ? 1 : 0;
    while (n != 0) {
        n = n / 16;
        length++;
    }
    return (length);
}

static void norme_loop(char* str, long unsigned int* n, int* length)
{
    while ((*n) != 0) {
        if ((*n) % 16 > 9)
            str[(*length)] = (*n) % 16 + 'a' - 10;
        else
            str[(*length)] = (*n) % 16 + '0';
        (*n) = (*n) / 16;
        (*length)--;
    }
}

char* ft_xlongtoa(long unsigned int n)
{
    char* str;
    int length;

    length = get_length(n);
    str = NULL;
    str = (char*)malloc(sizeof(char) * (length + 1));
    if (str) {
        str[length] = '\0';
        length--;
        str[length] = '0';
        norme_loop(str, &n, &length);
    }
    return str;
}

t_sym_l* new_symbol(char* sti, int type, uint64_t value)
{
    t_sym_l* s;
    char* v;

    s = malloc(sizeof(t_sym_l));
    s->sti = ft_strdup(sti);
    s->type = malloc(sizeof(int));
    (*s->type) = type;
    v = value_to_add(value);
    s->value = v;
    s->next = NULL;
    s->previous = NULL;
    return s;
}

void new_sym(t_sym_l** sym, t_h64 h, struct nlist_64 el)
{
    t_sym_l* s;

    s = new_symbol(h.stringtable + el.n_un.n_strx, type(&h.sectors, el.n_type, el.n_value ? 1 : 0, el.n_sect), el.n_value);
    sym_l_add(sym, s);
}

void pl(t_sym_l** s)
{
    t_sym_l* l;

    l = *s;
    while (l) {
        ft_putstr(l->value);
        ft_putchar(' ');
        ft_putchar((*l->type));
        ft_putchar(' ');
        ft_putstr(l->sti);
        ft_putchar('\n');
        l = l->next;
    }
}

int handle_output(t_h64 h)
{
    unsigned int i;
    i = -1;
    while (++i < h.sym->nsyms)
        new_sym(&h.symbols, h, h.el[i]);
    sym_l_sort(&h.symbols, sl);
    pl(&h.symbols);
    sym_l_del(&h.symbols);
    return EXIT_SUCCESS;
}