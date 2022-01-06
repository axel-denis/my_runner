/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** main.h
*/

#ifndef COLLISIONS_H
    #define COLLISIONS_H

    #include "../includes/csfml.h"
    #include "../includes/consts.h"
    #include "../includes/structs.h"
    #include "../includes/lib.h"
    #include "../includes/frees.h"
    #include "../includes/loaders.h"

int bottom_collision(gameobj *entity, map_col *map);
int soft_bottom_collision(gameobj *entity, map_col *map);
int front_collision(gameobj *entity, map_col *map);

#endif
