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

int handle_errors_env(t_env e)
{
	if (e.error)
	{
		ft_putendl_fd(e.error, 2);
		ft_strdel(&e.error);
	}
	return EXIT_FAILURE;
}

static int start(char *file, t_env e)
{
	int fd;
	char *ptr;
	struct stat buf;

	if (open_file(file, &fd, &ptr, &buf))
		return EXIT_FAILURE;
	if (handle_func(ptr)(e, ptr, buf.st_size))
		return handle_errors_env(e);
	if (close_file(&ptr, &fd, &buf))
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

void init_env(t_env *e)
{
	e->error = NULL;
}

int ft_nm(int ac, char **av)
{
	int i;
	t_env e;

	i = 1;
	init_env(&e);
	if (ac < 2)
	{
		if (start("a.out", e))
			return EXIT_FAILURE;
		return EXIT_SUCCESS;
	}
	while (ac > 1)
	{
		if (start(av[i], e))
			return EXIT_FAILURE;
		i++;
		ac--;
	}
	return (EXIT_SUCCESS);
}