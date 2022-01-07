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

gameobj *new_entity(const char *path_sprite, sfVector2f pos, int type)
{
    gameobj *obj = malloc(sizeof(gameobj));
    sfVector2f scale = {0.5, 0.5};

    obj->indice = type;
    obj->velocity.x = 0;
    obj->velocity.y = 0;
    obj->rect.top = 0;
    obj->rect.left = 0;
    obj->rect.width = 81;
    obj->rect.height = 60;
    obj->sprite = sfSprite_create();
    sfSprite_setTexture(obj->sprite, \
        sfTexture_createFromFile(path_sprite, NULL), sfTrue);
    if (type == 0)
        sfSprite_setTextureRect(obj->sprite, obj->rect);
    if (type == 2)
        sfSprite_setScale(obj->sprite, scale);
    sfSprite_setPosition(obj->sprite, pos);
    return obj;
}

parallax *new_mountain(void)
{
    parallax *first =  malloc(sizeof(parallax));
    parallax *actual = first;
    sfVector2f pos = {0, 0};
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
        sfSprite_setTexture(actual->sprite, \
            sfTexture_createFromFile(paths[i], NULL), sfTrue);
        sfSprite_setScale(actual->sprite, scale);
        if (i != 6) {
            actual->next = malloc(sizeof(parallax));
            actual = actual->next;
        } else
            actual->next = NULL;
    }
    return first;
}

parallax *new_industrial(void)
{
    parallax *first =  malloc(sizeof(parallax));
    parallax *actual = first;
    sfVector2f pos = {0, 0};
    sfVector2f scale;
    char *paths[] = {"assets/Layers/1.png", "assets/Layers/2.png",
    "assets/Layers/3.png", "assets/Layers/4.png", "assets/Layers/5.png", };

    scale.x = WIDTH / 576 + 1;
    scale.y = HEIGHT / 324 + 1;
    for (int i = 0; i < 5; i++) {
        actual->layer = i;
        actual->pos = pos;
        actual->sprite = sfSprite_create();
        sfSprite_setTexture(actual->sprite, \
            sfTexture_createFromFile(paths[i], NULL), sfTrue);
        sfSprite_setScale(actual->sprite, scale);
        if (i != 4) {
            actual->next = malloc(sizeof(parallax));
            actual = actual->next;
        } else
            actual->next = NULL;
    }
    return first;
}
