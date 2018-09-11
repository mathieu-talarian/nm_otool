#include <stdio.h>
#include "ft_nm.h"

int main(int ac, char **av)
{
    if (ft_nm(ac, av))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}