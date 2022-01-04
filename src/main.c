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

int bottom_collision(gameobj *entity, map_col *map, int x)
{
    float sprite_pos_y = sfSprite_getPosition(entity->sprite).y;
    float block_pos_y = 0.0;
    int col_to_check = 43; //(RABBIT_X + 40) / 32 + x - 61;
    int line_to_check = (sprite_pos_y + 61) / 32;

    printf("col_to_check = %d\nx = %d\nsprite_pos_y = %.2f\n", col_to_check, x - 61, sprite_pos_y);
    for (int i = 0; i < col_to_check; i++) {
        if (map->next == NULL)
            printf("WHY IS IT NULL AT i = %d?\n", i);
        map = map->next;
    }
    printf("was here with %d\n", line_to_check);
    block_pos_y = sfSprite_getPosition(map->col[line_to_check].sprite).y;
    printf("was after with %d\n", line_to_check);

    if (sprite_pos_y + 61 >= block_pos_y &&
        sprite_pos_y + 61 <= block_pos_y + 32 &&
        map->col[line_to_check].type > 0)
        printf("COLLISION\n");
    else
        printf("FREE\n");
}

void display_map(map_info *map, sfRenderWindow *window)
{
    map_col *actual = map->data;

    while (actual != NULL) {
        for (int i = 0; i < MAP_HEIGHT; i++)
            sfRenderWindow_drawSprite(window, actual->col[i].sprite, NULL);
        actual = actual->next;
    }
}

int main(void)
{
    map_info *map = map_creator();
    sfEvent event;
    sfRenderWindow *window = create_window();
    sfClock *clock = sfClock_create();
    sfTime time;
    float seconds;
    sfVector2f testpos = {500, 800};
    gameobj *rabbit = new_entity("assets/rabbit.png", testpos, 0);

    while (sfRenderWindow_isOpen(window)) {
        map_col *test = map->data;
        sfRenderWindow_clear(window, sfBlack);
        display_map(map, window);
        move_blocks(1, 5, map);
        bottom_collision(rabbit, map->data, map->iteration);
        sfRenderWindow_drawSprite(window, rabbit->sprite, NULL);
        time = sfClock_getElapsedTime(clock);
        seconds = time.microseconds / 1000000.0;
        //display_parallax(bg, window);
        sfRenderWindow_display(window);
        if (seconds >= .1) {
            animate(rabbit, 81, 316);
            sfClock_restart(clock);
        }
        while(sfRenderWindow_pollEvent(window, &event))
            event_handeling(event, window, rabbit);
    }
    free_map(map);
    return 0;
}
