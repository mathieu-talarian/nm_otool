#include "ft_nm.h"

int handle_error(t_env e, char *ptr, off_t size)
{
    off_t s;
    t_env d;

    s = size;
    d = e;
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