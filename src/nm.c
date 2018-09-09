#include "ft_nm.h"

#define FPFI(x, y, z) ft_putendl_fd_int(x, y, z)

int open_file(char *file, int *fd, char **ptr, struct stat *buf)
{
	if (((*fd) = open(file, O_RDONLY)) < 0)
		return ft_putendl_fd_int("Cant open file", 2, EXIT_FAILURE);
	if (fstat((*fd), *(&buf)) < 0)
		return ft_putendl_fd_int("Can't stat file", 2, EXIT_FAILURE);
	if (((*ptr) = mmap(0, (*buf).st_size, PROT_READ, MAP_PRIVATE, (*fd), 0)) == MAP_FAILED)
		return FPFI("Can't mmap", 2, EXIT_FAILURE);
	return EXIT_SUCCESS;
}

int close_file(char **ptr, int *fd, struct stat *buf)
{
	if (munmap((*ptr), (*buf).st_size) < 0)
		return FPFI("Can't unmap ptr", 0, EXIT_FAILURE);
	if (close((*fd)) < 0)
		return FPFI("Can't close file", 0, EXIT_FAILURE);
	return EXIT_SUCCESS;
}

static int start(char *file)
{
	int fd;
	char *ptr;
	struct stat buf;

	if (open_file(file, &fd, &ptr, &buf))
		return EXIT_FAILURE;
	if (handle_func(ptr)(ptr))
		return FPFI("Issue", 2, EXIT_FAILURE);
	if (close_file(&ptr, &fd, &buf))
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

int ft_nm(int ac, char **av)
{
	int i;

	i = 1;
	if (ac < 2)
		return (start("a.out"));
	while (ac > 1)
	{
		if (start(av[i]))
			return EXIT_FAILURE;
		i++;
		ac--;
	}
	return (EXIT_SUCCESS);
}