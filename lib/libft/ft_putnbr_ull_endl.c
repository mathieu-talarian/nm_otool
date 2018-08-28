#include "libft.h"

void ft_putnbr_ull(unsigned long long nbr)
{
    if (nbr >= 10)
    {
        ft_putnbr(nbr / 10);
        ft_putnbr(nbr % 10);
    }
    else
        ft_putchar(nbr + '0');
}

void ft_putnbr_ull_endl(unsigned long long nbr)
{
    ft_putnbr_ull(nbr);
    ft_putchar('\n');
}