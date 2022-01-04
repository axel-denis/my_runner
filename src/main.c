/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** main.c
*/

#include "../includes/csfml.h"
#include "../includes/consts.h"
#include "../includes/structs.h"
#include "../includes/lib.h"
#include "../includes/frees.h"
#include "../includes/loaders.h"

void event_handeling(sfEvent event, sfRenderWindow *window, gameobj *obj)
{
    sfVector2f vect;

    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyRight) {
        vect.x = 10;
        sfSprite_move(obj->sprite, vect);
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyLeft) {
        vect.x = -10;
        sfSprite_move(obj->sprite, vect);
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyUp) {
        vect.y = -10;
        sfSprite_move(obj->sprite, vect);
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyDown) {
        vect.y = 10;
        sfSprite_move(obj->sprite, vect);
    }
}

int main(void)
{
    map_info *map = map_creator();
    sfEvent event;
    sfRenderWindow *window = create_window();
    sfVector2f testpos;
    sfClock *clock = sfClock_create();
    sfTime time;
    float seconds;
    gameobj *obj = new_duck("assets/sprite.png", testpos);

    while (sfRenderWindow_isOpen(window)) {
        map_col *test = map->data;
        sfRenderWindow_clear(window, sfBlack);
        while (test != NULL) {
            for (int i = 0; i < MAP_HEIGHT; i++)
                sfRenderWindow_drawSprite(window, test->col[i].sprite, NULL);
            test = test->next;
        }
        move_blocks(1, 5, map);
        sfRenderWindow_drawSprite(window, obj->sprite, NULL);
        time = sfClock_getElapsedTime(clock);
        seconds = time.microseconds / 1000000.0;
        //display_parallax(bg, window);
        sfRenderWindow_display(window);
        if (seconds >= .2) {
            animate(obj, 110, 330);
            sfClock_restart(clock);
        }
        while(sfRenderWindow_pollEvent(window, &event))
            event_handeling(event, window, obj);
    }
    free_map(map);
    return 0;
}
