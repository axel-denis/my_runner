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
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeySpace) {
        printf("Space\n");
        obj->velocity.y = -20;
    }
}

//Vérifie les collisions pour le dessous du lapin à ses pixels 10 et 70
//(à 0 et 20 pixels du début et de la fin de la largeur du sprite, pour
//laisser une tolérance)
//Vérifie pour les colonnes 42 et 43, où se trouve toujours le lapin
int bottom_collision(gameobj *entity, map_col *map)
{
    float sprite_pos_y = sfSprite_getPosition(entity->sprite).y;
    float block_pos_y = 0.0;
    int line_to_check = (sprite_pos_y + 61) / 32;

    for (int i = 0; i < RABBIT_COL; i++)
        map = map->next;
    block_pos_y = sfSprite_getPosition(map->col[line_to_check].sprite).y;
    for (int i = 0; i < 2; i++) {
        if (sprite_pos_y + 60 >= block_pos_y &&
            sprite_pos_y + 60 <= block_pos_y + 32 &&
            map->col[line_to_check].type > 0)
            return 1;
        map = map->next;
    }
    return 0;
}

int front_collision(gameobj *entity, map_col *map)
{
    float sprite_pos_y = sfSprite_getPosition(entity->sprite).y;
    float block_pos_y = 0.0;
    int line_to_check = (sprite_pos_y + 61) / 32 - 1;

    for (int i = 0; i < RABBIT_COL + 1; i++)
        map = map->next;
    block_pos_y = sfSprite_getPosition(map->col[line_to_check].sprite).y;
    if (sprite_pos_y + 30 >= block_pos_y &&
        sprite_pos_y + 30 <= block_pos_y + 32 &&
        map->col[line_to_check].type > 0)
        return 1;
    return 0;
}

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

int conditions(sfRenderWindow *wind, map_info *map, gameobj *obj, parallax *bg)
{
    display_parallax(bg, wind);
    display_move_map(map, wind);
    bottom_collision(obj, map);
    if (front_collision(obj, map)) {
        return 1; // écran de perte
    }
    return 0;
}

int main(void)
{
    sfEvent event;
    map_info *map = map_creator();
    sfRenderWindow *window = create_window();
    sfClock *clock = sfClock_create();
    sfVector2f testpos = {500, 0};
    gameobj *rabbit = new_entity("assets/rabbit.png", testpos, 0);
    parallax *bg = new_industrial();

    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        conditions(window, map, rabbit, bg);
        animate_rabbit(rabbit, map, clock);
        sfRenderWindow_drawSprite(window, rabbit->sprite, NULL);
        sfRenderWindow_display(window);
        while(sfRenderWindow_pollEvent(window, &event))
            event_handeling(event, window, rabbit);
    }
    free_map(map);
    return 0;
}
