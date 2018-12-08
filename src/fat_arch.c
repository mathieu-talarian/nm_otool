/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_arch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 11:07:43 by mmoullec          #+#    #+#             */
/*   Updated: 2018/12/08 09:15:01 by mathieumo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char *get_cpu(int cputype)
{
    char *ret;

    ret = "";
    ret = cputype == CPU_TYPE_VAX ? "vax" : ret;
    ret = cputype == CPU_TYPE_MC680x0 ? "mc680x0" : ret;
    ret = cputype == CPU_TYPE_X86 ? "x86" : ret;
    ret = cputype == CPU_TYPE_I386 ? "i386" : ret;
    ret = cputype == CPU_TYPE_X86_64 ? "x86_64" : ret;
    ret = cputype == CPU_TYPE_MC98000 ? "mc98000" : ret;
    ret = cputype == CPU_TYPE_HPPA ? "hppa" : ret;
    ret = cputype == CPU_TYPE_ARM ? "arm" : ret;
    ret = cputype == CPU_TYPE_ARM64 ? "arm64" : ret;
    ret = cputype == CPU_TYPE_MC88000 ? "mc88000" : ret;
    ret = cputype == CPU_TYPE_SPARC ? "sparc" : ret;
    ret = cputype == CPU_TYPE_I860 ? "i860" : ret;
    ret = cputype == CPU_TYPE_POWERPC ? "ppc" : ret;
    ret = cputype == CPU_TYPE_POWERPC64 ? "ppc64" : ret;
    return (ret);
}
