#include "ft_nm.h"

int handle_error(char *ptr)
{
    printf("Issue");
    return EXIT_FAILURE;
}

HandleFunc handle_func(char *ptr)
{
    unsigned int magic_number;

    magic_number = *(unsigned int *)ptr;
    if (magic_number == MH_MAGIC_64)
        return handle_64;
    return handle_error;
}