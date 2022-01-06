/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** collisions.c
*/

#include "../includes/csfml.h"
#include "../includes/consts.h"
#include "../includes/structs.h"
#include "../includes/lib.h"
#include "../includes/frees.h"
#include "../includes/loaders.h"

//Vérifie les collisions pour le dessous du lapin à ses pixels 10 et 70
//(à 0 et 20 pixels du début et de la fin de la largeur du sprite, pour
//laisser une tolérance)
//Vérifie pour les colonnes 42 et 43, où se trouve toujours le lapin
int bottom_collision(gameobj *entity, map_col *map)
{
    float sprite_pos_y = sfSprite_getPosition(entity->sprite).y;
    float block_pos_y = 0.0;
    int line_to_check = (sprite_pos_y + 61) / 32;

    for (int i = 0; i < RABBIT_COL; i++)
        map = map->next;
    block_pos_y = sfSprite_getPosition(map->col[line_to_check].sprite).y;
    for (int i = 0; i < 2; i++) {
        if (sprite_pos_y + 60 >= block_pos_y &&
            sprite_pos_y + 60 <= block_pos_y + 32 &&
            map->col[line_to_check].type > 0)
            return 1;
        map = map->next;
    }
    return 0;
}

int soft_bottom_collision(gameobj *entity, map_col *map)
{
    float sprite_pos_y = sfSprite_getPosition(entity->sprite).y;
    float block_y = 0.0;
    int line_to_check = (sprite_pos_y + 61) / 32;

    for (int i = 0; i < RABBIT_COL; i++)
        map = map->next;
    for (int i = 0; i < 4; i++) {
        block_y = sfSprite_getPosition(map->col[line_to_check].sprite).y;
        if (sprite_pos_y + 60 >= block_y &&
            sprite_pos_y + 60 <= block_y + 32 &&
            map->col[line_to_check].type > 0)
            return 1;
        block_y = sfSprite_getPosition(map->col[line_to_check + 1].sprite).y;
        if (sprite_pos_y + 95 >= block_y &&
            sprite_pos_y + 95 <= block_y + 32 &&
            map->col[line_to_check + 1].type > 0)
            return 1;
        map = map->next;
    }
    return 0;
}

int front_collision(gameobj *entity, map_col *map)
{
    float sprite_pos_y = sfSprite_getPosition(entity->sprite).y;
    float block_pos_y = 0.0;
    int line_to_check = (sprite_pos_y + 61) / 32 - 1;

    for (int i = 0; i < RABBIT_COL; i++)
        map = map->next;
    block_pos_y = sfSprite_getPosition(map->col[line_to_check].sprite).y;
    if (sprite_pos_y + 30 >= block_pos_y &&
        sprite_pos_y + 30 <= block_pos_y + 32 &&
        map->col[line_to_check].type > 0)
        return 1;
    return 0;
}
