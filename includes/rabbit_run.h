/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** main.h
*/

#ifndef RABBIT_RUN
    #define RABBIT_RUN

    #include "../includes/csfml.h"
    #include "../includes/consts.h"
    #include "../includes/structs.h"
    #include "../includes/lib.h"
    #include "../includes/frees.h"
    #include "../includes/loaders.h"

void run_rabbit(gameobj *obj, sfClock *clock);
void velocity_up(gameobj *obj);
void gravity(gameobj *obj, map_info *map);
void animate_rabbit(gameobj *obj, map_info *map, sfClock *clock);

#endif
