/*
** EPITECH PROJECT, 2021
** bsmyprintf
** File description:
** my_put_nbr.c
*/

#include <unistd.h>

void my_put_nbr(int nb)
{
    char current_char = '-';

    if (nb < 0) {
        write(1, &current_char, 1);
        nb *= -1;
    }
    if (nb < 10 && nb >= 0) {
        current_char = nb + '0';
        write(1, &current_char, 1);
    } else {
        my_put_nbr(nb / 10);
        my_put_nbr(nb % 10);
    }
}
