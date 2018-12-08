#include "ft_nm.h"

int main(int ac, char **av)
{
    if (!ft_strcmp(av[0], "./ft_nm"))
    {
        if (ft_nm(ac, av))
            return EXIT_FAILURE;
    }
    else if (!ft_strcmp(av[0], "ft_otool"))
    {
    }
    return EXIT_SUCCESS;
}