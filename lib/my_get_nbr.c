/*
** EPITECH PROJECT, 2021
** bsbsq
** File description:
** my_get_nbr.c
*/

int my_strlen(char const *str);

int pw10(int x, int y)
{
    for (; y > 0; y--)
        x *= 10;
    return x;
}

int my_char_isnumeric(char letter)
{
    if (!(letter >= '0' && letter <= '9') && letter != '-' && letter != '+')
        return 0;
    return 1;
}

int boucle(int power, int i, int resultat)
{
    for (int k = power - i + 1; k > 0; k--)
        resultat /= 10;
    return resultat;
}

int my_get_nbr(char *str)
{
    int resultat = 0;
    int power = my_strlen(str) - 1;
    int j = 0;
    int parite = 1;

    for (;str[j] == '-' || str[j] == '+'; j++) {
        if (str[j] == '-')
            parite *= -1;
    }
    for (int i = j; i <= power; i++) {
        if (my_char_isnumeric(str[i])) {
            resultat += pw10(str[i] - '0', power - i);
        } else {
            resultat = boucle(power, i, resultat);
            break;
        }
    }
    if (parite == -1)
        resultat *= -1;
    return resultat;
}
