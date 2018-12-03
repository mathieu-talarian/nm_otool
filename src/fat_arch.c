/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_arch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 11:07:43 by mmoullec          #+#    #+#             */
/*   Updated: 2018/12/01 20:05:35 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int match_cpu_64(uint32_t nb_arch, struct fat_arch_64 *fat_arch)
{
    int i;

    i = -1;
    while (++i < nb_arch)
    {
        if (SwapInt(fat_arch->cputype) == CPU_TYPE_X86_64)
            return (1);
        fat_arch = (struct fat_arch_64 *) ((void *) fat_arch + sizeof(struct fat_arch_64));
    }
    return (0);
}

int handle_fat_arch_64(t_env *e, void *ptr, uint32_t nb_arch)
{
    struct fat_arch_64 *fat_arch;
    int                 matched;
    int                 used;
    int                 i;

    i = -1;
    used = 0;
    fat_arch = (struct fat_arch_64 *) ((void *) ptr + sizeof(struct fat_header));
    matched = match_cpu_64(nb_arch, fat_arch);
    e->opt = matched ? e->opt & ~NO_X86_64 : e->opt | NO_X86_64;
    while (++i < nb_arch)
    {
        // e->cputype
        if (!matched || (matched && SwapInt(fat_arch->cputype) == CPU_TYPE_X86_64 && !used++))
            return handle_macho(e, (void *) (ptr + SwapInt(fat_arch->offset)));
        fat_arch = (struct fat_arch_64 *) ((void *) ptr + sizeof(struct fat_arch_64));
    }
    return EXIT_FAILURE;
}

int handle_fat_arch(t_env *e, void *ptr, uint32_t nb_arch)
{
    return (0);
}
