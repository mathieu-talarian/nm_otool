#include "ft_nm.h"

int get_length(uint64_t value)
{
    int l;

    l = 1;
    while (value != 0)
    {
        value = value / 16;
        l++;
    }
    return l;
}

char *strzero(int l)
{
    char *ret;

    ret = malloc(sizeof(char) * (l + 1));
    ret[l] = 0;
    while (--l >= 0)
        ret[l] = '0';
    return ret;
}

#define R *ret

void addr(char *R, uint64_t value, int l)
{
    while (value != 0)
    {
        if ((value % 16) > 9)
            (R)[l] = value % 16 + 'a' - 10;
        else
            (R)[l] = value % 16 + '0';
        value = value / 16;
        l--;
    }
}

char *value_to_add(uint64_t value)
{
    char *ret;
    int   length;

    if (value == 0)
        return ft_strdup("                ");
    length = get_length(value);
    while (length++ < 14)
        ;
    ret = strzero(16);
    addr(&ret, value, length);
    return ret;
}
