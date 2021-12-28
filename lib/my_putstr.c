/*
** EPITECH PROJECT, 2021
** my_putstr
** File description:
** affiche un string
*/

void my_putchar(char c);

void my_putstr(char const *str)
{
    int count = 0;

    while (str[count]) {
        my_putchar(str[count]);
        count++;
    }
}
