/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** utils.h
*/

#ifndef UTILS_H
    #define UTILS_H

    #include "../includes/csfml.h"
    #include "../includes/consts.h"
    #include "../includes/structs.h"
    #include "../includes/lib.h"
    #include "../includes/frees.h"

int map_len(char *buffer);
void set_tile_rectangle(sfSprite *sprite, int top, int left);
sfSprite *block_sprite(int type, sfTexture *blocks_texture);
sfText *create_text(char *str, int size, sfVector2f pos, sfFont *font);

#endif
