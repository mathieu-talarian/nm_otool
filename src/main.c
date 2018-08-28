#include <stdio.h>
#include "ft_nm.h"

int main(int ac, char **av)
{
    int i;

    i = 1;
    if (ac < 2)
        return (0);
    while (ac > 1)
    {
        if (!ft_nm(av[i]))
            return (0);
        i++;
        ac--;
    }
    return (1);
}