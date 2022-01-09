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

int collision_slime(gameobj *rabbit)
{
    sfVector2f rabbit_pos = sfSprite_getPosition(rabbit->sprite);
    sfVector2f slime_pos = sfSprite_getPosition(rabbit->next->sprite);

    rabbit_pos.y += 15;
    if (!(rabbit_pos.x >= slime_pos.x && rabbit_pos.x <= slime_pos.x + 70))
        return 0;
    if (rabbit_pos.y >= slime_pos.y - 42 && rabbit_pos.y <= slime_pos.y - 22) {
        rabbit->velocity.y = -20;
        return 0;
    }
    if (rabbit_pos.y >= slime_pos.y - 32 && rabbit_pos.y <= slime_pos.y + 32)
        return 1;
    return 0;
}

//Vérifie les collisions pour le dessous du lapin à ses pixels 10 et 70
//(à 0 et 20 pixels du début et de la fin de la largeur du sprite, pour
//laisser une tolérance)
//Vérifie pour les colonnes ou se trouve l'entité uniquement
int bottom_collision(gameobj *entity, map_col *map)
{
    sfVector2f sprite_pos = sfSprite_getPosition(entity->sprite);
    float block_pos_y = 0.0;
    int line_to_check = (sprite_pos.y + 61) / 32;
    int col = RABBIT_COL;

    if (entity->indice == 1) {
        col = (int) (WIDTH - sprite_pos.x) / 32;
        line_to_check = (sprite_pos.y + SLIME_HEIGHT) / 32;
    }
    for (int i = 0; i < col; i++)
        map = map->next;
    block_pos_y = sfSprite_getPosition(map->col[line_to_check].sprite).y;
    for (int i = 0; i < 2; i++) {
        if (line_to_check * 32 >= block_pos_y &&
            line_to_check * 32 <= block_pos_y + 32 &&
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
        if (sprite_pos_y + 61 >= block_y &&
            sprite_pos_y + 61 <= block_y + 32 &&
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
    sfVector2f sprite_pos = sfSprite_getPosition(entity->sprite);
    float block_pos_y = 0.0;
    int line_to_check = (sprite_pos.y + 61) / 32 - 1;
    int col = RABBIT_COL;

    if (entity->indice == 1) {
        col = (int) (WIDTH - sprite_pos.x) / 32 + 2;
        line_to_check = (sprite_pos.y + SLIME_HEIGHT) / 32 - 1;
    }
    for (int i = 0; i < col; i++)
        map = map->next;
    block_pos_y = sfSprite_getPosition(map->col[line_to_check].sprite).y;
    if (line_to_check * 32 >= block_pos_y &&
        line_to_check * 32 <= block_pos_y + 32 &&
        map->col[line_to_check].type > 0)
        return 1;
    return 0;
}
