/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** structs.h
*/

#include "csfml.h"

typedef struct block {
    sfVector2f pos;
    sfSprite *sprite;
    int type;
    int final_y;
    //int base_x;
    //int base_y;
} block;


//NOTE on va faire une pile parce que grace à ça les blocs à bouger (qui
// demandent donc d'accéder à la structure) sont au début
// la variable col est un array de struct block
typedef struct map_col {
    block *col;
    struct map_col *next;
} map_col;

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

parallax *new_mountain(sfRenderWindow *window);
parallax *new_industrial(sfRenderWindow *window);
void display_parallax(parallax *layers, sfRenderWindow *window);

map_col *map_init(char *buffer, int map_len, sfTexture *texture);
