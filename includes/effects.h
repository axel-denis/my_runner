/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** effects.h
*/

#ifndef EFFECT_H
    #define EFFECT_H

    #include "../includes/csfml.h"
    #include "../includes/consts.h"
    #include "../includes/structs.h"
    #include "../includes/lib.h"
    #include "../includes/frees.h"
    #include "../includes/utils.h"
    #include "../includes/loaders.h"

void block_height_effect(block *block);
void blocks_effect(map_col *map);
void set_effect(map_col *actual, sfVector2f pos, int i);

#endif
