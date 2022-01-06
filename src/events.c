/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** events.c
*/

#include "../includes/csfml.h"
#include "../includes/consts.h"
#include "../includes/structs.h"
#include "../includes/lib.h"
#include "../includes/frees.h"
#include "../includes/loaders.h"
#include "../includes/collisions.h"

int evts(sfEvent event, sfRenderWindow *window, gameobj *obj, map_info *map)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(window);

    if (event.type == sfEvtMouseButtonPressed && pos.x > 620 && pos.x < 1235 \
        && pos.y > 450 && pos.y < 650) {
        return 2;
    }
    if (event.type == sfEvtMouseButtonPressed) {
        if (soft_bottom_collision(obj, map->data)) {
            sfMusic_stop(map->sounds[2]);
            sfMusic_play(map->sounds[2]);
            obj->velocity.y = -20;
        }
        return 0;
    }
    return 0;
}

int events(sfEvent event, sfRenderWindow *window, gameobj *obj, map_info *map)
{
    if (event.type == sfEvtClosed) {
        sfRenderWindow_close(window);
        return -1;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape) {
        sfRenderWindow_close(window);
        return -1;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeySpace) {
        if (soft_bottom_collision(obj, map->data)) {;
            sfMusic_stop(map->sounds[2]);
            sfMusic_play(map->sounds[2]);
            obj->velocity.y = -20;
        }
        return 0;
    }
    return evts(event, window, obj, map);
}
