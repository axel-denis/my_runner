/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** main.h
*/

#ifndef EVENTS_H
    #define EVENTS_H

    #include "../includes/csfml.h"
    #include "../includes/consts.h"
    #include "../includes/structs.h"
    #include "../includes/lib.h"
    #include "../includes/frees.h"
    #include "../includes/loaders.h"

int events(sfEvent event, sfRenderWindow *window, gameobj *obj, map_info *map);
int evts(sfEvent event, sfRenderWindow *window, gameobj *obj, map_info *map);

#endif
