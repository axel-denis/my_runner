/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** structs.h
*/

#include "csfml.h"


typedef struct gameobj {
    int indice;
    sfVector2f pos;
    sfSprite *sprite;
    sfTexture *texture;
    sfIntRect rect;
} gameobj;

gameobj *new_duck(const char *path_sprite, sfVector2f pos);
void move_rect(sfIntRect *rect, int offset, int max);
