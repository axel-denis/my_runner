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

void display_move_map(map_info *map, sfRenderWindow *window)
{
    map_col *actual = NULL;

    if (move_blocks(1, 5, map) == 1)
        return 1;
    actual = map->data;
    while (actual != NULL) {
        for (int i = 0; i < MAP_HEIGHT; i++)
            sfRenderWindow_drawSprite(window, actual->col[i].sprite, NULL);
        actual = actual->next;
    }
    return 0;
}

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
    sfVector2f txt_pos = {600, 500};

    sfSprite_setTexture(bg, bg_color, sfTrue);
    sfSprite_setScale(bg, screen_scale);
    sfSprite_setTexture(win, win_img, sfTrue);
    sfSprite_setScale(win, scale_win);
    sfSprite_setPosition(win, win_pos);
    game_over_display(bg, win, map, window);
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
