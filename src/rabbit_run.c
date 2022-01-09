/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** rabbit_run.c
*/

#include "../includes/csfml.h"
#include "../includes/consts.h"
#include "../includes/structs.h"
#include "../includes/lib.h"
#include "../includes/frees.h"
#include "../includes/utils.h"
#include "../includes/collisions.h"

void run_rabbit(gameobj *obj, sfClock *clock)
{
    sfTime time = sfClock_getElapsedTime(clock);
    float seconds = time.microseconds / 1000000.0;

    if (obj->velocity.y > 1) {
        obj->rect.left = RABBIT_WIDTH * 3;
        sfSprite_setTextureRect(obj->sprite, obj->rect);
        return;
    } else if (obj->velocity.y < 0) {
        obj->rect.left = RABBIT_WIDTH * 2;
        sfSprite_setTextureRect(obj->sprite, obj->rect);
        return;
    }
    if (seconds >= 0.1) {
        if (obj->rect.left + RABBIT_WIDTH >= RABBIT_WIDTH * 4)
            obj->rect.left = 0;
        else
            obj->rect.left += RABBIT_WIDTH;
        sfSprite_setTextureRect(obj->sprite, obj->rect);
        sfClock_restart(clock);
    }
}

void velocity_up(gameobj *obj)
{
    float to_y = sfSprite_getPosition(obj->sprite).y + obj->velocity.y;
    float y_pos = sfSprite_getPosition(obj->sprite).y;
    sfVector2f move_vect = {0, -1};

    while (y_pos > to_y) {
        y_pos--;
        sfSprite_move(obj->sprite, move_vect);
    }
    if (obj->velocity.y > -1)
        obj->velocity.y = 0;
    obj->velocity.y /= 1.2;
}

int gravity(gameobj *obj, map_info *map)
{
    float to_y = sfSprite_getPosition(obj->sprite).y + obj->velocity.y;
    float y_pos = sfSprite_getPosition(obj->sprite).y;
    sfVector2f move_vect = {0, 1};

    if (obj->velocity.y == 0.0) {
        obj->velocity.y = 1.0;
        return 0;
    }
    while (y_pos < to_y && !bottom_collision(obj, map->data)) {
        y_pos++;
        sfSprite_move(obj->sprite, move_vect);
    }
    if (bottom_collision(obj, map->data) == 1)
        obj->velocity.y = 0;
    else if (obj->velocity.y > 0 && obj->velocity.y < 20)
        obj->velocity.y *= 1.2;
    else
        obj->velocity.y /= 1.2;
    return bottom_collision(obj, map->data);
}

int animate_rabbit(gameobj *obj, map_info *map, sfClock *clock)
{
    int state = 0;

    run_rabbit(obj, clock);
    if (obj->velocity.y >= 0)
        state = gravity(obj, map);
    else
        velocity_up(obj);
    return state;
}
