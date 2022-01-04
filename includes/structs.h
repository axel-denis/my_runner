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
    int final_y;
} block;

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

typedef struct map_info {
    char *buffer;
    map_col *data;
    parallax *bg;
    int iteration;
    int len;
    sfTexture *texture;
} map_info;

map_col *map_col_reader(char *buffer, int x, int map_len, sfTexture *texture,
                        float last_pos);

gameobj *new_entity(const char *path_sprite, sfVector2f pos, int type);
void animate(gameobj *obj, int offset, int max);
void move_blocks(int direction, int speed, map_info *map);

parallax *new_mountain();
parallax *new_industrial();
void display_parallax(parallax *layers, sfRenderWindow *window);

map_col *map_init(char *buffer, int map_len, sfTexture *texture);
void free_col(map_col *col);

#endif
