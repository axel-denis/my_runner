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

int events(sfEvent event, sfRenderWindow *window, gameobj *obj, map_info *map)
{
    sfVector2f vect;

    if (event.type == sfEvtClosed) {
        sfRenderWindow_close(window);
        return -1;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape) {
        sfRenderWindow_close(window);
        return -1;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeySpace) {
        printf("space\n");
        if (soft_bottom_collision(obj, map))
            obj->velocity.y = -20;
        return 2;
    }
    return 0;
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

int soft_bottom_collision(gameobj *entity, map_col *map)
{
    float sprite_pos_y = sfSprite_getPosition(entity->sprite).y;
    float block_y = 0.0;
    int line_to_check = (sprite_pos_y + 61) / 32;

    for (int i = 0; i < RABBIT_COL; i++)
        map = map->next;
    for (int i = 0; i < 4; i++) {
        block_y = sfSprite_getPosition(map->col[line_to_check].sprite).y;
        if (sprite_pos_y + 60 >= block_y &&
            sprite_pos_y + 60 <= block_y + 32 &&
            map->col[line_to_check].type > 0)
            return 1;
        block_y = sfSprite_getPosition(map->col[line_to_check + 1].sprite).y;
        if (sprite_pos_y + 95 >= block_y &&
            sprite_pos_y + 95 <= block_y + 32 &&
            map->col[line_to_check + 1].type > 0)
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

int main_menu(sfRenderWindow *window, gameobj *rabbit, map_info *map)
{
    sfEvent event;
    parallax *bg = new_mountain();
    int condition = 0;

    while (condition == 0) {
        sfRenderWindow_clear(window, sfBlack);
        display_parallax(bg, window);
        sfRenderWindow_drawText(window, map->text.text, NULL);
        sfRenderWindow_display(window);
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
            printf("mort\n");
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
