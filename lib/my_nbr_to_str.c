/*
** EPITECH PROJECT, 2021
** my_put_nbr
** File description:
** affiche le nombre donné en parametre. Marche avec un int
*/

#include <stdlib.h>

int power_ten(int x, int y)
{
    for (y; y > 0; y--) {
        x = x * 10;
    }
    return (x);
}

int length(int nb)
{
    int count = 0;

    while (nb >= 10) {
        count++;
        nb /= 10;
    }
    return count + 1;
}

char *my_nbr_to_str(int nb)
{
    int len = length(nb);
    char *str = malloc(len + 1);

    str[len] = '\0';
    while (len > 0) {
        str[len - 1] = nb % 10 + '0';
        nb /= 10;
        len--;
    }
    return str;
}
