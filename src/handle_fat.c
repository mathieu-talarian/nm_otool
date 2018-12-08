/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 04:40:51 by mmoullec          #+#    #+#             */
/*   Updated: 2018/12/08 12:00:36 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void match_cpu_64(uint32_t nb_arch, struct fat_arch_64 *fat_arch, int *opt, int *matched)
{
    uint32_t i;

    i = -1;
    *matched = 0;
    while (++i < nb_arch)
    {
        if (SwapInt(fat_arch->cputype) == CPU_TYPE_X86_64)
        {
            *opt &= ~NO_X86_64;
            *matched = 1;
            return;
        }
        fat_arch = (struct fat_arch_64 *) ((void *) fat_arch + sizeof(struct fat_arch_64));
    }
    *opt |= NO_X86_64;
}

int handle_fat_arch_64(t_env *e, void *ptr, uint32_t nb_arch)
{
    struct fat_arch_64 *fat_arch;
    int                 used;
    uint32_t            i;
    int                 matched;

    i = -1;
    used = 0;
    fat_arch = (struct fat_arch_64 *) ((void *) ptr + sizeof(struct fat_header));
    match_cpu_64(nb_arch, fat_arch, &e->opt, &matched);
    while (++i < nb_arch)
    {
        e->cputype = get_cpu(SwapInt(fat_arch->cputype));
        if (!matched || (matched && SwapInt(fat_arch->cputype) == CPU_TYPE_X86_64 && !used++))
            return handle_macho(e, (void *) (ptr + SwapInt(fat_arch->offset)));
        fat_arch = (struct fat_arch_64 *) ((void *) ptr + sizeof(struct fat_arch_64));
    }
    return EXIT_FAILURE;
}

void match_cpu(uint32_t nb_arch, struct fat_arch *fat_arch, int *opt, int *matched)
{
    uint32_t i;

    *matched = 0;
    i = -1;
    while (++i < nb_arch)
    {
        if (SwapInt(fat_arch->cputype) == CPU_TYPE_X86_64)
        {
            *opt &= ~NO_X86_64;
            *matched = 1;
            return;
        }
        fat_arch = (struct fat_arch *) ((void *) fat_arch + sizeof(struct fat_arch));
    }
    *opt |= NO_X86_64;
}

int handle_fat_arch(t_env *e, void *ptr, uint32_t nb_arch)
{
    struct fat_arch *fat_arch;
    int              used;
    uint32_t         i;
    int              matched;

    i = -1;
    used = 0;
    fat_arch = (struct fat_arch *) ((void *) ptr + sizeof(struct fat_header));
    match_cpu(nb_arch, fat_arch, &e->opt, &matched);
    while (++i < nb_arch)
    {
        e->cputype = get_cpu(SwapInt(fat_arch->cputype));
        if (!matched || (matched && SwapInt(fat_arch->cputype) == CPU_TYPE_X86_64 && !used++))
            return handle_macho(e, (void *) (ptr + SwapInt(fat_arch->offset)));
        fat_arch = (struct fat_arch *) ((void *) ptr + sizeof(struct fat_arch));
    }
    return EXIT_FAILURE;
}

int handle_fat(t_env *e, char *ptr)
{
    struct fat_header *fat;
    fat = (struct fat_header *) ptr;

    if (fat->magic == FAT_MAGIC_64 || fat->magic == FAT_CIGAM_64)
        return handle_fat_arch_64(e, ptr, SwapInt(fat->nfat_arch));
    else
        return handle_fat_arch(e, ptr, SwapInt(fat->nfat_arch));
}
