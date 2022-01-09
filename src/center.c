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

int collision_slime(gameobj *rabbit)
{
    sfVector2f rabbit_pos = sfSprite_getPosition(rabbit->sprite);
    sfVector2f slime_pos = sfSprite_getPosition(rabbit->next->sprite);

    rabbit_pos.y += 15;
    printf("rabbit pos : %f %f\nslime pos : %f %f\n", rabbit_pos.x, rabbit_pos.y, slime_pos.x, slime_pos.y);
    if (!(rabbit_pos.x >= slime_pos.x && rabbit_pos.x <= slime_pos.x + 70))
        return 0;
    if (rabbit_pos.y >= slime_pos.y - 42 && rabbit_pos.y <= slime_pos.y - 22) {
        printf("will jump\n");
        rabbit->velocity.y = -20;
        return 0;
    }
    if (rabbit_pos.y >= slime_pos.y - 32 && rabbit_pos.y <= slime_pos.y + 32) {
        printf("eu\n");
        return 1;
    }
    return 0;
}
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

int main(void)
{
    sfVector2f testpos = {500, 300};
    gameobj *rabbit = new_entity("assets/rabbit.png", testpos, 0);
    map_info *map = map_creator(malloc(sizeof(map_info)));
    sfRenderWindow *window = create_window();

    testpos.x = WIDTH + 1;
    rabbit->next = new_slime("assets/slime.png", testpos);
    if (main_menu(window, rabbit, map) == -1)
        return 0;
    main_process(map, rabbit, window);
    free_entity(rabbit);
    return 0;
}
