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

t_symbols *init_t_s()
{
    t_symbols *s;

    if (!(s = malloc(sizeof(t_symbols))))
        return NULL;
    s->type = 0;
    s->value = 0;
    s->sti = NULL;
    return s;
}

void handle_print_value(long int value)
{
    char *v;
    v = ft_xlongtoa(value);
    ft_putstr(v);
    ft_strdel(&v);
}

void print_list(t_list **l)
{
    t_list *list;

    list = *l;
    while (list)
    {
        t_symbols *s = (t_symbols *)list->content;
        //printf("%c\n", s->type);
        handle_print_value(s->value);
        ft_putchar(s->type);
        ft_putendl(s->sti);
        list = list->next;
    }
}

int sl(t_list *el1, t_list *el2)
{
    t_symbols *e1;
    t_symbols *e2;
    e1 = (t_symbols *)el1->content;
    e2 = (t_symbols *)el2->content;
    return ft_strcmp(e1->sti, e2->sti);
}

void del(void *content, size_t c_size)
{
    t_symbols *s;

    s = (t_symbols *)content;
    ft_strdel(&s->sti);
    ft_strdel((char **)&content);
}

void del_s(void *content, size_t c_size)
{
    t_sectors *s;

    s = (t_sectors *)content;
    ft_strdel(&s->name);
    ft_strdel((char **)&content);
}

void new_symbols(t_symbols *s, char *sti, char type, uint64_t value)
{
    s->sti = ft_strdup(sti);
    s->type = (char)type;
    s->value = (long int)value;
}

void new_sym(t_list **list, t_h64 h, struct nlist_64 el)
{
    t_symbols s;

    new_symbols(&s, h.stringtable + el.n_un.n_strx, type(&h.sec, el.n_type, el.n_value ? 1 : 0, el.n_sect), el.n_value);
    ft_lstadd(list, ft_lstnew(&s, sizeof(t_symbols)));
}

int handle_output(t_h64 h)
{
    unsigned int i;

    i = -1;
    while (++i < h.sym->nsyms)
        new_sym(&h.list, h, h.el[i]);
    ft_lstsort(&h.list, &sl);
    print_list(&h.list);
    ft_lstdel(&h.list, del);
    ft_lstdel(&h.sec, del_s);
    h.list = NULL;
    h.sec = NULL;
    return EXIT_SUCCESS;
}