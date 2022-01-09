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
#include "../includes/slime.h"

int main_disp(sfRenderWindow *wind, map_info *map, gameobj *obj, parallax *bg)
{
    sfVector2f pos = sfSprite_getPosition(obj->sprite);
    char *str = my_nbr_to_str(map->iteration);

    display_parallax(bg, wind);
    if (display_move_map(map, wind) == 1)
        return 2;
    if (pos.y >= HEIGHT - 80 || pos.y <= 0)
        return 1;
    if (front_collision(obj, map->data))
        return 1;
    slime_gestion(obj->next, map, wind);
    if (collision_slime(obj) == 1)
        return 1;
    animate_rabbit(obj, map, map->clock);
    sfText_setString(map->text.text, str);
    sfRenderWindow_drawText(wind, map->text.text, NULL);
    sfRenderWindow_drawSprite(wind, obj->sprite, NULL);
    free(str);
    return 0;
}

int main_process(map_info *map, gameobj *rabbit, sfRenderWindow *window)
{
    sfEvent event;
    parallax *bg = new_industrial();
    int end = 0;

    while (sfRenderWindow_isOpen(window) && end == 0) {
        sfRenderWindow_clear(window, sfBlack);
        end = main_disp(window, map, rabbit, bg);
        sfRenderWindow_display(window);
        while (sfRenderWindow_pollEvent(window, &event))
            events(event, window, rabbit, map);
    }
    if (end == 1)
        game_over_setup(window, map);
    else if (end == 2)
        win_setup(window, map);
    free_map(map);
    free_parallax(bg);
    sfRenderWindow_destroy(window);
    return 0;
}

int main(int ac, char **av)
{
    sfVector2f testpos = {500, 300};
    gameobj *rabbit;
    map_info *map;
    sfRenderWindow *window;

    if (ac != 2)
        return 84;
    if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0')
        return usage();
    map = map_creator(malloc(sizeof(map_info)), av[1]);
    if (map == NULL) {
        my_putstr("Error while loading this map.\n");
        return 84;
    }
    rabbit = new_entity("assets/rabbit.png", testpos, 0);
    testpos.x = WIDTH + 1;
    window = create_window();
    rabbit->next = new_slime("assets/slime.png", testpos);
    if (main_menu(window, rabbit, map) == -1)
        return 0;
    main_process(map, rabbit, window);
    free_entity(rabbit);
    return 0;
}
