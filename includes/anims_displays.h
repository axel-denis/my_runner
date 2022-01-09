/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** anims_displays.h
*/

#ifndef ANIM_DISPLAYS_H
    #define ANIM_DISPLAYS_H

    #include "../includes/csfml.h"
    #include "../includes/consts.h"
    #include "../includes/structs.h"
    #include "../includes/lib.h"
    #include "../includes/frees.h"
    #include "../includes/utils.h"

int display_move_map(map_info *map, sfRenderWindow *window);
void display_parallax(parallax *layers, sfRenderWindow *window);
map_col *next_col(map_info *map, map_col *last, map_col *actual, \
    sfVector2f first_pos);
map_col *map_col_reader(char *buffer, int x, int map_len, sfTexture *texture,
                        float last_pos);
int move_blocks(int direction, int speed, map_info *map);
void move_one_block(map_col *actual, int speed, int direction);

#endif
