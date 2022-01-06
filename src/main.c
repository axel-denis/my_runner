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

    move_blocks(1, 5, map);
    actual = map->data;
    while (actual != NULL) {
        for (int i = 0; i < MAP_HEIGHT; i++)
            sfRenderWindow_drawSprite(window, actual->col[i].sprite, NULL);
        actual = actual->next;
    }
}

int process(sfRenderWindow *wind, map_info *map, gameobj *obj, parallax *bg)
{
    sfVector2f pos = sfSprite_getPosition(obj->sprite);

    display_parallax(bg, wind);
    display_move_map(map, wind);
    if (pos.y >= HEIGHT - 80 || pos.y <= 0)
        return 1;
    if (front_collision(obj, map->data))
        return 1; // écran de perte
    animate_rabbit(obj, map, map->clock);
    sfText_setString(map->text.text, my_nbr_to_str(map->iteration));
    sfRenderWindow_drawText(wind, map->text.text, NULL);
    return 0;
}

int main(void)
{
    sfEvent event;
    map_info *map = map_creator();
    sfRenderWindow *window = create_window();
    sfVector2f testpos = {500, 300};
    gameobj *rabbit = new_entity("assets/rabbit.png", testpos, 0);
    parallax *bg = new_industrial();

    if (main_menu(window, rabbit, map) == -1)
        return 0;
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        if (process(window, map, rabbit, bg)) {
            printf("mort");
            exit(0);
        }
        sfRenderWindow_drawSprite(window, rabbit->sprite, NULL);
        sfRenderWindow_display(window);
        while(sfRenderWindow_pollEvent(window, &event))
            events(event, window, rabbit, map);
    }
    free_map(map);
    return 0;
}
