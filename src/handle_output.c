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
    int length;

    length = get_length(n);
    str = NULL;
    str = (char *)malloc(sizeof(char) * (length + 1));
    if (str)
    {
        str[length] = '\0';
        length--;
        str[length] = '0';
        norme_loop(str, &n, &length);
    }
    return str;
}

// // t_symbols *init_t_s()
// // {
// //     t_symbols *s;

// //     if (!(s = (t_symbols *)malloc(sizeof(t_symbols))))
// //         return NULL;
// //     s->type = NULL;
// //     s->value = NULL;
// //     s->sti = NULL;
// //     return s;
// // }

// void print_list(t_list **l)
// {
//     t_list *list;

//     list = *l;
//     while (list)
//     {
//         t_symbols *s = (t_symbols *)list->content;
//         printf("%s ", s->value);
//         printf("%s \n", s->sti);

//         list = list->next;
//     }
// }

// void del(void *content, size_t c_size)
// {
//     t_symbols *s;

//     s = (t_symbols *)content;
//     ft_strdel(&s->sti);
//     ft_strdel(&s->value);
//     ft_strdel((char **)&content);
// }

// void del_s(void *content, size_t c_size)
// {
//     t_sectors *s;

//     s = (t_sectors *)content;
//     ft_strdel(&s->name);
//     ft_strdel((char **)&content);
// }

// int handle_output(t_h64 h)
// {
//     unsigned int i;

//     i = -1;
//     while (++i < h.sym->nsyms)
//         new_sym(&h.list, h, h.el[i]);
//     ft_lstsort(&h.list, &sl);
//     //print_list(&h.list);
//     ft_lstdel(&h.list, del);
//     ft_lstdel(&h.sec, del_s);
//     return EXIT_SUCCESS;
// }

t_sym_l *new_symbol(char *sti, int type, uint64_t value)
{
    t_sym_l *s;
    char *v;

    s = malloc(sizeof(t_sym_l));
    s->sti = ft_strdup(sti);
    s->type = type;
    v = ft_xlongtoa(value);
    s->value = v;
    s->next = NULL;
    s->previous = NULL;
    return s;
}

void new_sym(t_sym_l **sym, t_h64 h, struct nlist_64 el)
{
    t_sym_l *s;

    s = new_symbol(h.stringtable + el.n_un.n_strx, type(&h.sectors, el.n_type, el.n_value ? 1 : 0, el.n_sect), el.n_value);
    sym_l_add(sym, s);
}

void pl(t_sym_l **s)
{
    t_sym_l *l;

    l = *s;
    while (l)
    {
        printf("%s\n", l->sti);
        l = l->next;
    }
    l = *s;
    while (l->next)
        l = l->next;
    printf("\n");
    while (l)
    {
        printf("%s\n", l->sti);
        l = l->previous;
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