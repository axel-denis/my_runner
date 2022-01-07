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
#include "../includes/events.h"
#include "../includes/rabbit_run.h"
#include "../includes/collisions.h"
#include "../includes/menus.h"
#include "../includes/endscreens.h"
#include "../includes/anims_displays.h"

int process(sfRenderWindow *wind, map_info *map, gameobj *obj, parallax *bg)
{
    sfVector2f pos = sfSprite_getPosition(obj->sprite);

    display_parallax(bg, wind);
    display_move_map(map, wind);
    if (pos.y >= HEIGHT - 80 || pos.y <= 0)
        return 2;
    if (front_collision(obj, map->data))
        return 1;
    animate_rabbit(obj, map, map->clock);
    sfText_setString(map->text.text, my_nbr_to_str(map->iteration));
    sfRenderWindow_drawText(wind, map->text.text, NULL);
    sfRenderWindow_drawSprite(wind, obj->sprite, NULL);
    return 0;
}

int main_process(map_info *map, gameobj *rabbit, sfRenderWindow *window)
{
    sfEvent event;
    parallax *bg = new_industrial();
    int end = 0;

    while (sfRenderWindow_isOpen(window) && end == 0) {
        sfRenderWindow_clear(window, sfBlack);
        end = process(window, map, rabbit, bg);
        sfRenderWindow_display(window);
        while (sfRenderWindow_pollEvent(window, &event))
            events(event, window, rabbit, map);
    }
    printf("end = %d\n", end);
    if (end == 1)
        game_over_setup(window, map);
    //else
    //    win();
    sfRenderWindow_destroy(window);
    free_map(map);
    return 0;
}

int main(void)
{
    sfVector2f testpos = {500, 300};
    gameobj *rabbit = new_entity("assets/rabbit.png", testpos, 0);
    map_info *map = map_creator(malloc(sizeof(map_info)));
    sfRenderWindow *window = create_window();

    if (main_menu(window, rabbit, map) == -1)
        return 0;
    main_process(map, rabbit, window);
}
