// #include "ft_nm.h"

// static int n_value(uint64_t value)
// {
//     return printf("%s\n", ft_xlongtoa(value));
// }

// static int n_sect(unsigned int m)
// {
//     return m == N_SECT ? printf("N_SECT\n") : 0;
// }

// static int n_stab(unsigned int m)
// {
//     return m == N_STAB ? printf("N_STAB\n") : 0;
// }

// static int handle_output(struct symtab_command *sym, char *ptr)
// {
//     unsigned int i;
//     char *stringtable;
//     struct nlist_64 *el;

//     el = (void *)ptr + sym->symoff;
//     stringtable = (void *)ptr + sym->stroff;
//     i = 0;
//     while (i < sym->nsyms)
//     {
//         printf("%d\n", el[i].n_type & N_STAB);
//         printf("%d\n", el[i].n_type & N_TYPE);
//         if (n_sect(el[i].n_type & N_TYPE))
//         {
//             n_value(el[i].n_value);
//         }
//         n_stab(el[i].n_type & N_TYPE);
//         printf("=> %s\n", stringtable + el[i].n_un.n_strx);
//         i++;
//     }
//     return 1;
// }

// int handle_64(char *ptr)
// {


//     i = -1;
//     header = (struct mach_header_64 *)ptr;
//     ncmds = header->ncmds;
//     lc = (void *)ptr + sizeof(struct mach_header_64);
//     while (++i < ncmds)
//     {
//         if (lc->cmd == LC_SYMTAB)
//         {
//             sym = (struct symtab_command *)lc;
//             return handle_output(sym, ptr);
//         }
//         lc = (void *)lc + lc->cmdsize;
//     }
//     return (1);
// }