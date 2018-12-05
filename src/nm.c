/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:15:06 by mmoullec          #+#    #+#             */
/*   Updated: 2018/12/05 07:47:41 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#define FPFI(x, y, z) ft_putendl_fd_int(x, y, z)

int open_file(char *file, int *fd, char **ptr, struct stat *buf, t_env *e)
{
    if (((*fd) = open(file, O_RDONLY)) < 0)
        return ft_putendl_fd_int("Cant open file", 2, EXIT_FAILURE);
    if (fstat((*fd), *(&buf)) < 0)
        return ft_putendl_fd_int("Can't stat file", 2, EXIT_FAILURE);
    e->filesize = buf->st_size;
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
        // ft_putendl_fd(e.error, 2);
        // ft_strdel(&e.error);
    }
    return EXIT_FAILURE;
}

void identify_file(char *file, char *ptr, t_env *e)
{
    unsigned int magic_number;

    e->title = file;
    magic_number = *(int *) ptr;
    if (magic_number == FAT_MAGIC || magic_number == FAT_MAGIC_64 || magic_number == FAT_CIGAM || magic_number == FAT_CIGAM_64)
    {
        e->opt = e->opt | FAT;
    }
    else
        e->opt = e->opt & ~FAT;
    if ((ft_strncmp(ARMAG, (char *) ptr, 8)) == 0)
        e->opt |= LIB;
    else
        e->opt &= ~LIB;
}

static int start(char *file, t_env *e)
{
    int         fd;
    char *      ptr;
    struct stat buf;

    if (open_file(file, &fd, &ptr, &buf, e))
        return EXIT_FAILURE;
    identify_file(file, ptr, e);
    if (handle_func(e->opt)(e, ptr))
        return handle_errors_env(*e);
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
    int   i;
    t_env e;

    i = 1;
    init_env(&e);
    if (ac == 1)
    {
        av[1] = "a.out";
        ac = 2;
    }
    while (ac > 1)
    {
        if (start(av[i], &e))
            return EXIT_FAILURE;
        i++;
        ac--;
    }
    return (EXIT_SUCCESS);
}