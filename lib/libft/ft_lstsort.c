#include "libft.h"

void ft_lstswap(t_list *l, t_list *next)
{
    void *tmp_c;
    size_t tmp_s;

    if (l && next)
    {
        tmp_c = l->content;
        tmp_s = l->content_size;
        l->content = next->content;
        l->content_size = next->content_size;
        next->content = tmp_c;
        next->content_size = tmp_s;
    }
}

void ft_lstsort(t_list **lst, int (*f)(t_list *el1, t_list *el2))
{
    t_list *l = *lst;

    while (l && l->next)
    {
        if (f(l, l->next) > 0)
        {
            ft_lstswap(l, l->next);
            return ft_lstsort(lst, f);
        }
        l = l->next;
    }
}