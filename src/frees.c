/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** frees.c
*/

#include "../includes/consts.h"
#include "../includes/csfml.h"
#include "../includes/lib.h"
#include "../includes/structs.h"

void free_col(map_col *col)
{
    if (col->next != NULL)
        free_col(col->next);
    for (int i = 0; i < MAP_HEIGHT; i++)
        sfSprite_destroy(col->col[i].sprite);
    free(col->col);
    free(col);
}

void free_parallax(parallax *bg)
{
    if (bg->next != NULL)
        free_parallax(bg->next);
    sfSprite_destroy(bg->sprite);
    free(bg);
}

void free_map(map_info *map)
{
    free(map->buffer);
    free_col(map->data);
    free_parallax(map->bg);
    sfTexture_destroy(map->texture);
    free(map);
}
