#include "ft_nm.h"

#define FPFI(x, y, z) ft_putendl_fd_int(x, y, z)

static int handle_64(char *ptr)
{
    return (1);
}

static int nm(char *ptr)
{
    int magic_number;

    magic_number = *(int *)ptr;
    printf("%d\n", (int)magic_number);
    if (magic_number == MH_MAGIC_64)
        return handle_64(ptr);
    return (0);
}

int ft_nm(char *file)
{
    int fd;
    char *ptr;
    struct stat buf;

    if ((fd = open(file, O_RDONLY)) < 0)
        return ft_putendl_fd_int("Cant open file", 2, EXIT_FAILURE);
    if (fstat(fd, &buf) < 0)
        return ft_putendl_fd_int("Can't stat file", 2, EXIT_FAILURE);
    if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
        return FPFI("Can't mmap", 2, EXIT_FAILURE);
    if (!nm(ptr))
        return FPFI("Issue", 2, EXIT_FAILURE);
    if (munmap(ptr, buf.st_size) < 0)
        return FPFI("Can't unmap ptr", 0, EXIT_FAILURE);
    
    return EXIT_SUCCESS;
}