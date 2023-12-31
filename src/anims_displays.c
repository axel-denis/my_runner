/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** anims_displays.c
*/

#include "../includes/csfml.h"
#include "../includes/consts.h"
#include "../includes/structs.h"
#include "../includes/lib.h"
#include "../includes/frees.h"
#include "../includes/utils.h"
#include "../includes/loaders.h"
#include "../includes/effects.h"

map_col *next_col(map_info *map, map_col *last, map_col *actual, \
    sfVector2f first_pos)
{
    map_col *temp = actual;
    last->next = NULL;
    free_col(temp);
    map->iteration += 1;
    temp = map_col_reader(map->buffer, map->iteration, \
        map->len, map->texture, first_pos.x);
    if (temp == NULL)
        return temp;
    temp->next = map->data;
    map->data = temp;
    return temp;
}

void move_one_block(map_col *actual, int speed, int direction)
{
    sfVector2f offset;

    for (int i = 0; i < MAP_HEIGHT; i++) {
        offset = sfSprite_getPosition(actual->col[i].sprite);
        offset.x = offset.x - speed * direction;
        sfSprite_setPosition(actual->col[i].sprite, offset);
    }
}

int move_blocks(int direction, int speed, map_info *map)
{
    map_col *last = map->data;
    map_col *actual = map->data;
    sfVector2f first_pos;

    while (actual != NULL) {
        first_pos = sfSprite_getPosition(actual->col[0].sprite);
        if (first_pos.x <= (-32 * direction))
            actual = next_col(map, last, actual, first_pos);
        if (actual == NULL)
            return 1;
        move_one_block(actual, speed, direction);
        last = actual;
        actual = actual->next;
    }
    return 0;
}

int display_move_map(map_info *map, sfRenderWindow *window)
{
    map_col *actual = NULL;

    if (move_blocks(1, 5, map) == 1)
        return 1;
    blocks_effect(map->data);
    actual = map->data;
    while (actual != NULL) {
        for (int i = 0; i < MAP_HEIGHT; i++)
            sfRenderWindow_drawSprite(window, actual->col[i].sprite, NULL);
        actual = actual->next;
    }
    return 0;
}

void display_parallax(parallax *layers, sfRenderWindow *window)
{
    sfVector2f go_right;
    sfVector2f go_left;

    go_right.x = WIDTH;
    go_left.x = -WIDTH;
    while (layers != NULL) {
        sfRenderWindow_drawSprite(window, layers->sprite, NULL);
        sfSprite_move(layers->sprite, go_right);
        sfRenderWindow_drawSprite(window, layers->sprite, NULL);
        sfSprite_move(layers->sprite, go_left);
        layers->pos.x -= layers->layer / 3.0;
        sfSprite_setPosition(layers->sprite, layers->pos);
        if (sfSprite_getPosition(layers->sprite).x <= -WIDTH)
            layers->pos.x = 0;
        layers = layers->next;
    }
}
