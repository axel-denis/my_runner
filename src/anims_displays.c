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

void move_blocks(int direction, int speed, map_info *map)
{
    map_col *last = map->data;
    map_col *actual = map->data;
    map_col *temp = NULL;
    sfVector2f offset;// = {speed * direction, 0};
    sfVector2f first_pos;

    while (actual != NULL) {
        first_pos = sfSprite_getPosition(actual->col[0].sprite);
        if (first_pos.x <= (-32 * direction)) {
            temp = actual;
            last->next = NULL;
            free_col(temp);
            map->iteration += 1;
            temp = map_col_reader(map->buffer, map->iteration,
                                  map->len, map->texture, first_pos.x);
            temp->next = map->data;
            map->data = temp;
            actual = temp;
        } else {
        }
        for (int i = 0; i < MAP_HEIGHT; i++) {
            offset = sfSprite_getPosition(actual->col[i].sprite);
            offset.x = offset.x - speed * direction;
            sfSprite_setPosition(actual->col[i].sprite, offset);
        }
        last = actual;
        actual = actual->next;
    }
    return;
}
