/*
** EPITECH PROJECT, 2021
** my_putstr
** File description:
** affiche un string
*/

int my_strlen(char const *str)
{
    int count = 0;

    while (str[count]) {
        count++;
    }
    return (count);
}
