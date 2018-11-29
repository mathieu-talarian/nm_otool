#include "ft_nm.h"

int is_corrupted(unsigned char* ptr, void* file, off_t size)
{
    if (ptr < (unsigned char*)file)
        return EXIT_FAILURE;
    if (ptr > (unsigned char*)((unsigned char*)file + size))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}