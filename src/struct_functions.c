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

gameobj *new_slime(const char *path_sprite, sfVector2f pos)
{
    gameobj *obj = malloc(sizeof(gameobj));
    sfVector2f scale = {2, 2};

    obj->indice = 1;
    obj->velocity.x = 0;
    obj->velocity.y = 0;
    obj->rect.top = 0;
    obj->rect.left = 0;
    obj->rect.width = SLIME_WIDTH;
    obj->rect.height = SLIME_HEIGHT / 2;
    obj->sprite = sfSprite_create();
    obj->texture = sfTexture_createFromFile(path_sprite, NULL);
    sfSprite_setTexture(obj->sprite, obj->texture, sfTrue);
    sfSprite_setTextureRect(obj->sprite, obj->rect);
    sfSprite_setScale(obj->sprite, scale);
    sfSprite_setPosition(obj->sprite, pos);
    return obj;
}

gameobj *new_entity(const char *path_sprite, sfVector2f pos, int type)
{
    gameobj *obj = malloc(sizeof(gameobj));
    sfVector2f scale = {10, 10};

    obj->indice = type;
    obj->velocity.x = 0;
    obj->velocity.y = 0;
    obj->rect.top = 0;
    obj->rect.left = 0;
    obj->rect.width = 81;
    obj->rect.height = 60;
    obj->sprite = sfSprite_create();
    obj->texture = sfTexture_createFromFile(path_sprite, NULL);
    sfSprite_setTexture(obj->sprite, obj->texture, sfTrue);
    if (type == 0)
        sfSprite_setTextureRect(obj->sprite, obj->rect);
    if (type == 2)
        sfSprite_setScale(obj->sprite, scale);
    sfSprite_setPosition(obj->sprite, pos);
    return obj;
}

void mount_layer(parallax *actual, char *path, int index, sfVector2f scale)
{
    sfVector2f pos = {0, 0};

    actual->layer = index;
    actual->pos = pos;
    actual->sprite = sfSprite_create();
    actual->texture = sfTexture_createFromFile(path, NULL);
    sfSprite_setTexture(actual->sprite, actual->texture, sfTrue);
    sfSprite_setScale(actual->sprite, scale);
}

parallax *new_mountain(void)
{
    parallax *first =  malloc(sizeof(parallax));
    parallax *actual = first;
    sfVector2f scale;
    char *paths[] = {"assets/layers/mountains1.png",
    "assets/layers/mountains2.png", "assets/layers/mountains3.png",
    "assets/layers/mountains4.png", "assets/layers/mountains5.png",
    "assets/layers/mountains6.png", "assets/layers/mountains7.png"};

    scale.x = WIDTH / PARALLAX_WIDTH + 1;
    scale.y = HEIGHT / PARALLAX_HEIGHT + 1;
    for (int i = 0; i < 7; i++) {
        mount_layer(actual, paths[i], i, scale);
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
    sfVector2f scale;
    char *paths[] = {"assets/layers/indu1.png", "assets/layers/indu2.png",
    "assets/layers/indu3.png", "assets/layers/indu4.png",
    "assets/layers/indu5.png"};

    scale.x = WIDTH / 576 + 1;
    scale.y = HEIGHT / 324 + 1;
    for (int i = 0; i < 5; i++) {
        mount_layer(actual, paths[i], i, scale);
        if (i != 4) {
            actual->next = malloc(sizeof(parallax));
            actual = actual->next;
        } else
            actual->next = NULL;
    }
    return first;
}
