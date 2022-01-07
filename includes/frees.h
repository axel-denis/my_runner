/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** frees.h
*/

#ifndef FREES_H
    #define FREES_H

    #include "consts.h"
    #include "csfml.h"
    #include "lib.h"
    #include "structs.h"

void free_col(map_col *col);
void free_parallax(parallax *bg);
void free_map(map_info *map);
void free_entity(gameobj *entity);

#endif
