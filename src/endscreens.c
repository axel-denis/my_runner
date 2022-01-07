/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** endscreens.c
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

void game_over_display(sfSprite *background, sfSprite *title, map_info *map, \
    sfRenderWindow *window)
{
    int end = 0;
    sfEvent event;
    sfVector2f txt_pos = {600, 500};
    sfText_setString(map->text.text, "Press ESCAPE to quit");
    sfText_setPosition(map->text.text, txt_pos);
    sfRenderWindow_drawSprite(window, background, NULL);
    sfRenderWindow_drawSprite(window, title, NULL);
    sfRenderWindow_drawText(window, map->text.text, NULL);
    sfRenderWindow_display(window);
    while (end == 0) {
        while (sfRenderWindow_pollEvent(window, &event))
            end += esc_events(event, window);
    }
}

void game_over_setup(sfRenderWindow *window, map_info *map)
{
    sfSprite *bg = sfSprite_create();
    sfTexture *bg_color = sfTexture_createFromFile("assets/blank.png", NULL);
    sfSprite *win = sfSprite_create();
    sfTexture *win_img = sfTexture_createFromFile("assets/gameover.png", NULL);
    sfVector2f screen_scale = {WIDTH, HEIGHT};
    sfVector2f scale_win = {6, 6};
    sfVector2f win_pos = {575, 100};

    sfSprite_setTexture(bg, bg_color, sfTrue);
    sfSprite_setScale(bg, screen_scale);
    sfSprite_setTexture(win, win_img, sfTrue);
    sfSprite_setScale(win, scale_win);
    sfSprite_setPosition(win, win_pos);
    game_over_display(bg, win, map, window);
}
