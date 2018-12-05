#include "ft_nm.h"

struct load_command swap_lc_cmd(struct load_command *load_command)
{
    struct load_command lc;

    lc = *load_command;
    lc.cmd = SwapInt(load_command->cmd);
    lc.cmdsize = SwapInt(load_command->cmdsize);
    return lc;
}