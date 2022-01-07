/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** structs.h
*/

#ifndef STRUCTS_H
    #define STRUCTS_H
    #include "csfml.h"

typedef struct block {
    sfVector2f pos;
    sfSprite *sprite;
    int type;
} block;

typedef struct map_col {
    block *col;
    struct map_col *next;
} map_col;

typedef struct gameobj {
    int indice;
    sfVector2f velocity;
    sfSprite *sprite;
    sfIntRect rect;
    struct gameobj *next;
} gameobj;

typedef struct parallax {
    int layer;
    sfVector2f pos;
    sfSprite *sprite;
    struct parallax *next;
} parallax;

typedef struct texts {
    sfFont *font;
    sfText *text;
    sfVector2f pos;
} texts;

typedef struct map_info {
    char *buffer;
    map_col *data;
    parallax *bg;
    int iteration;
    texts text;
    int len;
    sfTexture *texture;
    sfClock *clock;
    sfMusic *sounds[3];
} map_info;

#endif
