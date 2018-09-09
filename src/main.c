#include <stdio.h>
#include "ft_nm.h"

int main(int ac, char **av)
{
    int b;
    while (1) 
    {
        if (ft_nm(ac, av))
            return EXIT_FAILURE;
        scanf("%d", &b);
    }
    return 0;//ft_nm(ac, av);
}