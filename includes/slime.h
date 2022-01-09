/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** slime.h
*/

#ifndef SLIME_H
    #define SLIME_H

    #include "../includes/csfml.h"
    #include "../includes/consts.h"
    #include "../includes/structs.h"
    #include "../includes/lib.h"
    #include "../includes/frees.h"
    #include "../includes/loaders.h"

sfVector2f find_ground(gameobj *slime, map_info *map);
void slime_gestion(gameobj *slime, map_info *map, sfRenderWindow *window);

#endif
