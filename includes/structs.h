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
    sfIntRect rect;
    struct gameobj *next;
} gameobj;

typedef struct parallax {
    int layer;
    sfVector2f pos;
    sfSprite *sprite;
    struct parallax *next;
} parallax;

gameobj *new_duck(const char *path_sprite, sfVector2f pos);
void animate(gameobj *obj, int offset, int max);

parallax *new_parallax(sfRenderWindow *window);
void display_parallax(parallax *layers, sfRenderWindow *window);
