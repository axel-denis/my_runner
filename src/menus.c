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

void show_menu(sfRenderWindow *win, parallax *bg, sfText *title, gameobj *but)
{
    sfRenderWindow_clear(win, sfBlack);
    display_parallax(bg, win);
    sfRenderWindow_drawText(win, title, NULL);
    sfRenderWindow_drawSprite(win, but->sprite, NULL);
    sfRenderWindow_display(win);
}

int main_menu(sfRenderWindow *window, gameobj *rabbit, map_info *map)
{
    sfEvent event;
    parallax *bg = new_mountain();
    int condition = 0;
    sfVector2f pos = {610, 450};
    gameobj *button = new_entity("assets/start.png", pos, 2);

    while (condition == 0) {
        show_menu(window, bg, map->text.text, button);
        while(sfRenderWindow_pollEvent(window, &event))
            condition += events(event, window, rabbit, map);
    }
    free_parallax(bg);
    sfText_setCharacterSize(map->text.text, 66);
    sfText_setOutlineColor(map->text.text, sfBlack);
    sfText_setOutlineThickness(map->text.text, 2);
    map->text.pos.y = 33;
    map->text.pos.x = 66;
    sfText_setPosition(map->text.text, map->text.pos);
    return condition;
}
