/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** effects.c
*/

#include "../includes/csfml.h"
#include "../includes/consts.h"
#include "../includes/structs.h"
#include "../includes/lib.h"
#include "../includes/frees.h"
#include "../includes/utils.h"
#include "../includes/loaders.h"
#include "../includes/effects.h"

void block_height_effect(block *block)
{
    sfVector2f pos = sfSprite_getPosition(block->sprite);
    sfVector2f scale = sfSprite_getScale(block->sprite);

    if (pos.x < 200) {
        pos.y -= 1;
        scale.x -= 0.02;
        scale.y -= 0.02;
    } else if (scale.x != 1 && scale.y != 1) {
        scale.x += 0.02;
        scale.y += 0.02;
    }
    if (pos.y != block->pos.y)
        pos.y -= 1;
    if (scale.x > 1 || scale.y > 1) {
        scale.x = 1;
        scale.y = 1;
    }

    sfSprite_setScale(block->sprite, scale);
    sfSprite_setPosition(block->sprite, pos);
}

void blocks_effect(map_col *map)
{
    while (map != NULL) {
        for (int i = 0; i < MAP_HEIGHT; i++)
            block_height_effect(&(map->col[i]));
        map = map->next;
    }
}

void set_effect(map_col *actual, sfVector2f pos, int i)
{
    sfVector2f scale = {0.4, 0.4};

    sfSprite_setPosition(actual->col[i].sprite, pos);
    sfSprite_setScale(actual->col[i].sprite, scale);
}
