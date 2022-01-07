/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** loaders.h
*/

#ifndef LOADERS_H
    #define LOADERS_H

    #include "../includes/csfml.h"
    #include "../includes/consts.h"
    #include "../includes/structs.h"
    #include "../includes/lib.h"
    #include "../includes/frees.h"

char *read_map_file(char *map_file);
sfRenderWindow *create_window(void);
map_info *map_creator(map_info *map);
map_col *map_col_reader(char *buffer, int x, int map_len, sfTexture *texture,
                        float last_pos);
map_col *map_init(char *buffer, int map_len, sfTexture *texture);

#endif
