/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** slime.c
*/

#include "../includes/csfml.h"
#include "../includes/consts.h"
#include "../includes/structs.h"
#include "../includes/lib.h"
#include "../includes/frees.h"
#include "../includes/loaders.h"
#include "../includes/events.h"
#include "../includes/rabbit_run.h"
#include "../includes/collisions.h"
#include "../includes/menus.h"
#include "../includes/endscreens.h"
#include "../includes/anims_displays.h"

sfVector2f find_ground(gameobj *slime, map_info *map)
{
    sfVector2f pos = {WIDTH - 1, HEIGHT / 2};

    sfSprite_setPosition(slime->sprite, pos);
    while (!bottom_collision(slime, map->data) && pos.y < HEIGHT - 23) {
        pos.y += 1;
        sfSprite_setPosition(slime->sprite, pos);
    }
    sfSprite_setPosition(slime->sprite, pos);
    if (pos.y >= HEIGHT - 24) {
        pos.y = 0;
        pos.x = -33;
        slime->rect.left = SLIME_WIDTH * 4;
    } else
        slime->rect.left = 0;
    sfSprite_setTextureRect(slime->sprite, slime->rect);
    return pos;
}

void slime_gestion(gameobj *slim, map_info *map, sfRenderWindow *window)
{
    sfVector2f pos = sfSprite_getPosition(slim->sprite);
    sfTime time = sfClock_getElapsedTime(map->clock);
    float seconds = time.microseconds / 1000000.0;

    if (slim->velocity.y >= 0 && pos.x > 1 && pos.y < HEIGHT - SLIME_HEIGHT)
        gravity(slim, map);
    pos = sfSprite_getPosition(slim->sprite);
    if (pos.x > 15 && !front_collision(slim, map->data))
        pos.x -= 8;
    else
        pos.x -= 6;
    if (pos.x < -32 || pos.y >= HEIGHT - SLIME_HEIGHT)
        pos = find_ground(slim, map);
    if (seconds >= 0.1 && !(pos.x < -32)) {
        slim->rect.left = (slim->rect.left + SLIME_WIDTH) % (SLIME_WIDTH * 4);
        sfSprite_setTextureRect(slim->sprite, slim->rect);
    }
    sfSprite_setPosition(slim->sprite, pos);
    sfRenderWindow_drawSprite(window, slim->sprite, NULL);
}
