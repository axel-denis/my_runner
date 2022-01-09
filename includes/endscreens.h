/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** main.h
*/

#ifndef END_H
    #define END_H

    #include "../includes/csfml.h"
    #include "../includes/consts.h"
    #include "../includes/structs.h"
    #include "../includes/lib.h"
    #include "../includes/frees.h"
    #include "../includes/loaders.h"

void end_screen(sfSprite *background, sfSprite *title, map_info *map, \
    sfRenderWindow *window);
void game_over_setup(sfRenderWindow *window, map_info *map);
void win_setup(sfRenderWindow *window, map_info *map);
void pause_setup(sfRenderWindow *window, map_info *map);

#endif
