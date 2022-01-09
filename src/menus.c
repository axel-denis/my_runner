/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** menus.c
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
#include "../includes/anims_displays.h"

void show_menu(sfRenderWindow *win, map_info *map, gameobj *but)
{
    sfRenderWindow_clear(win, sfBlack);
    display_parallax(map->bg, win);
    sfRenderWindow_drawText(win, map->text.text, NULL);
    sfRenderWindow_drawSprite(win, but->sprite, NULL);
    sfRenderWindow_display(win);
}

void reconfigure_text(map_info *map)
{
    sfText_setCharacterSize(map->text.text, 66);
    sfText_setOutlineColor(map->text.text, sfBlack);
    sfText_setOutlineThickness(map->text.text, 2);
    map->text.pos.y = 33;
    map->text.pos.x = 66;
    sfText_setPosition(map->text.text, map->text.pos);
}

int main_menu(sfRenderWindow *window, gameobj *rabbit, map_info *map)
{
    sfEvent event;
    int condition = 0;
    sfVector2f pos = {600, 450};
    gameobj *button = new_entity("assets/start.png", pos, 2);

    sfMusic_play(map->sounds[0]);
    while (condition == 0) {
        show_menu(window, map, button);
        while (sfRenderWindow_pollEvent(window, &event))
            condition += events(event, window, rabbit, map);
    }
    sfMusic_pause(map->sounds[0]);
    sfMusic_play(map->sounds[1]);
    reconfigure_text(map);
    free_entity(button);
    return condition;
}

int usage(void)
{
    my_putstr("Finite runner created with CSFML\n");
    my_putstr("Created by Axel Denis for Epitech.\n");
    my_putstr("\nUSAGE\n ./my_runner map.txt\n");
    my_putstr("\nOPTIONS\n -h\tprints the usage and quit.\n");
    my_putstr("\nUSER INTERACTIONS\n SPACE_KEY\tjump.\nESCAPE_KEY\texit game.");
    my_putstr("\n\n");
    return 0;
}
