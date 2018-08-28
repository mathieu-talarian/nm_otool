#ifndef FT_NM_H
#define FT_NM_H

#include "../lib/libft/libft.h"

#include <stdio.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/stab.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int ft_nm(char *filename);

#endif