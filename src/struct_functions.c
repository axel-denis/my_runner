/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** struct_functions.c
*/

#include "../includes/csfml.h"
#include "../includes/structs.h"
#include "../includes/consts.h"
#include "../includes/lib.h"

gameobj *new_duck(const char *path_sprite, sfVector2f pos)
{
    gameobj *obj = malloc(sizeof(gameobj));

    obj->indice = 0;
    obj->pos = pos;
    obj->rect.top = 0;
    obj->rect.left = 0;
    obj->rect.width = 110;
    obj->rect.height = 110;
    //obj->texture = sfTexture_createFromFile(path_sprite, NULL);
    obj->sprite = sfSprite_create();
    sfSprite_setTexture(obj->sprite, sfTexture_createFromFile(path_sprite, NULL), sfTrue);
    sfSprite_setTextureRect(obj->sprite, obj->rect);
    return obj;
}

parallax *new_mountain(sfRenderWindow *window)
{
    parallax *first =  malloc(sizeof(parallax));
    parallax *actual = first;
    sfVector2f pos;
    sfVector2f scale;
    char *paths[] = {"assets/Layers/sky.png", "assets/Layers/clouds_bg.png",
    "assets/Layers/glacial_mountains_lightened.png",
    "assets/Layers/cloud_lonely.png", "assets/Layers/clouds_mg_3.png",
    "assets/Layers/clouds_mg_2.png", "assets/Layers/clouds_mg_1.png"};

    scale.x = WIDTH / PARALLAX_WIDTH + 1;
    scale.y = HEIGHT / PARALLAX_HEIGHT + 1;
    for (int i = 0; i < 7; i++) {
        actual->layer = i;
        actual->pos = pos;
        actual->sprite = sfSprite_create();
        sfSprite_setTexture(actual->sprite, sfTexture_createFromFile(paths[i], NULL), sfTrue);
        sfSprite_setScale(actual->sprite, scale);
        if (i != 6) {
            actual->next = malloc(sizeof(parallax));
            actual = actual->next;
        } else
            actual->next = NULL;
    }
    return first;
}

parallax *new_industrial(sfRenderWindow *window)
{
    parallax *first =  malloc(sizeof(parallax));
    parallax *actual = first;
    sfVector2f pos;
    sfVector2f scale;
    char *paths[] = {"assets/Layers/1.png", "assets/Layers/2.png",
    "assets/Layers/3.png", "assets/Layers/4.png", "assets/Layers/5.png", };

    scale.x = WIDTH / 576 + 1;
    scale.y = HEIGHT / 324 + 1;
    for (int i = 0; i < 5; i++) {
        actual->layer = i;
        actual->pos = pos;
        actual->sprite = sfSprite_create();
        sfSprite_setTexture(actual->sprite, sfTexture_createFromFile(paths[i], NULL), sfTrue);
        sfSprite_setScale(actual->sprite, scale);
        if (i != 4) {
            actual->next = malloc(sizeof(parallax));
            actual = actual->next;
        } else
            actual->next = NULL;
    }
    return first;
}

void display_parallax(parallax *layers, sfRenderWindow *window)
{
    sfVector2f go_right;
    sfVector2f go_left;
    sfVector2f reset;

    go_right.x = WIDTH;
    go_left.x = -WIDTH;
    reset.x = 0;
    reset.y = 0;
    while (layers != NULL) {
        sfRenderWindow_drawSprite(window, layers->sprite, NULL);
        sfSprite_move(layers->sprite, go_right);
        sfRenderWindow_drawSprite(window, layers->sprite, NULL);
        sfSprite_move(layers->sprite, go_left);
        layers->pos.x -= layers->layer / 3.0;
        sfSprite_setPosition(layers->sprite, layers->pos);
        if (sfSprite_getPosition(layers->sprite).x <= -WIDTH)
            layers->pos.x = 0;
        layers = layers->next;
    }
}

void animate(gameobj *obj, int offset, int max)
{
    if (obj->rect.left + offset >= max)
        obj->rect.left = 0;
    else
        obj->rect.left += offset;
    sfSprite_setTextureRect(obj->sprite, obj->rect);
}


sfSprite *block_sprite(int type, sfTexture *blocks_texture)
{
    sfSprite *sprite = sfSprite_create();
    sfIntRect rectangle = {32 * 4, 0, 32, 32};

    if (type == 0) {
        sfSprite_setTexture(sprite, blocks_texture, sfTrue);
        sfSprite_setTextureRect(sprite, rectangle);
    }
    return sprite;
}

map_col *map_col_reader(char *buffer, int x, int map_len, sfTexture *texture)
{
    map_col *actual = malloc(sizeof(map_col));
    int tmp_final_y = 0;
    actual->col = malloc(sizeof(block) * MAP_HEIGHT); // hauteur arbitraire de 20
    actual->next = NULL;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        actual->col[i].pos.x = x * 32;
        actual->col[i].pos.y = i * 32;
        tmp_final_y = my_get_nbr(&buffer[(x * CHUNK) + ((map_len * CHUNK + 2) * i) + 1]); // mauvais ici, on lit pas le bon endroit à chaque fois
        actual->col[i].final_y = tmp_final_y;
        actual->col[i].type = (int) (buffer[(x * CHUNK) + ((map_len * CHUNK + 2) * i)] - '0');
        actual->col[i].sprite = block_sprite(actual->col[i].type, texture);
        sfSprite_setPosition(actual->col[i].sprite, actual->col[i].pos);
    }
    return actual;
}

map_col *map_init(char *buffer, int map_len, sfTexture *texture)
{
    map_col *temp_node = NULL;
    map_col *new_temp_node = NULL;

    for (int index = 0; index < 60; index++) {
        new_temp_node = map_col_reader(buffer, index, map_len, texture);
        new_temp_node->next = temp_node;
        temp_node = new_temp_node;
    }
    return temp_node;
}
