#include "ft_nm.h"

t_sym_l *sym_l_new(char *pre, char type, char *start)
{
    t_sym_l *sym;

    sym = (t_sym_l *) malloc(sizeof(t_sym_l));
    if (sym != NULL)
    {
        sym->type = type;
        sym->sti = ft_strdup(start);
        sym->value = ft_strdup(pre);
        return sym;
    }
    return (NULL);
}

void sym_l_add(t_sym_l **symbols, t_sym_l *new)
{
    if (new)
    {
        new->next = *symbols;
        *symbols = new;
        new->previous = NULL;
        if (new->next)
            new->next->previous = new;
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
        ft_strdel((char **) &l);
        l = n;
    }
    *symbols = NULL;
}

int sl(char *el1, char *el2)
{
    return ft_strcmp(el1, el2);
}

void swap_i(char *ptr1, char *ptr2)
{
    int tmp;
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

t_sym_l *getTail(t_sym_l *cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

// Partitions the list taking the last element as the pivot
t_sym_l *partition(t_sym_l *head, t_sym_l *end, t_sym_l **newHead, t_sym_l **newEnd, int (*f)(char *el1, char *el2))
{
    t_sym_l *pivot = end;
    t_sym_l *prev = NULL, *cur = head, *tail = pivot;

    // During partition, both the head and end of the list might change
    // which is updated in the newHead and newEnd variables
    while (cur != pivot)
    {
        if (f(cur->sti, pivot->sti) < 0)
        {
            // First node that has a value less than the pivot - becomes
            // the new head
            if ((*newHead) == NULL)
                (*newHead) = cur;

            prev = cur;
            cur = cur->next;
        }
        else // If cur node is greater than pivot
        {
            // Move cur node to next of tail, and change tail
            if (prev)
                prev->next = cur->next;
            t_sym_l *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    // If the pivot data is the smallest element in the current list,
    // pivot becomes the head
    if ((*newHead) == NULL)
        (*newHead) = pivot;

    // Update newEnd to the current last node
    (*newEnd) = tail;

    // Return the pivot node
    return pivot;
}

// here the sorting happens exclusive of the end node
t_sym_l *quickSortRecur(t_sym_l *head, t_sym_l *end, int (*f)(char *el1, char *el2))
{
    // base condition
    if (!head || head == end)
        return head;

    t_sym_l *newHead = NULL, *newEnd = NULL;

    // Partition the list, newHead and newEnd will be updated
    // by the partition function
    t_sym_l *pivot = partition(head, end, &newHead, &newEnd, f);

    // If pivot is the smallest element - no need to recur for
    // the left part.
    if (newHead != pivot)
    {
        // Set the node before the pivot node as NULL
        t_sym_l *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;

        // Recur for the list before pivot
        newHead = quickSortRecur(newHead, tmp, f);

        // Change next of last node of the left half to pivot
        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    // Recur for the list after the pivot element
    pivot->next = quickSortRecur(pivot->next, newEnd, f);

    return newHead;
}

void sym_l_sort(t_sym_l **head_ref, int (*f)(char *el1, char *el2))
{
    (*head_ref) = quickSortRecur(*head_ref, getTail(*head_ref), f);
    return;
}
