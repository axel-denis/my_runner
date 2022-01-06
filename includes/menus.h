/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** main.h
*/

#ifndef MENUS_H
    #define MENUS_H

    #include "../includes/csfml.h"
    #include "../includes/consts.h"
    #include "../includes/structs.h"
    #include "../includes/lib.h"
    #include "../includes/frees.h"
    #include "../includes/loaders.h"

int main_menu(sfRenderWindow *window, gameobj *rabbit, map_info *map);
void show_menu(sfRenderWindow *win, parallax *bg, sfText *title, gameobj *but);

#endif
