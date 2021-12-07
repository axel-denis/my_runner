/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** struct_functions.c
*/

#include "includes/csfml.h"
#include "includes/structs.h"

gameobj *new_duck(const char *path_sprite, sfVector2f pos)
{
    gameobj *obj = malloc(sizeof(gameobj));

    obj->indice = 0;
    obj->pos = pos;
    obj->rect.top = 0;
    obj->rect.left = 0;
    obj->rect.width = 110;
    obj->rect.height = 110;
    obj->texture = sfTexture_createFromFile(path_sprite, NULL);
    obj->sprite = sfSprite_create();
    sfSprite_setTexture(obj->sprite, obj->texture, sfTrue);
    sfSprite_setTextureRect(obj->sprite, obj->rect);
    return obj;
}

void animate(gameobj *obj, int offset, int max)
{
    printf("%d\n", obj->rect.left);
    if (obj->rect.left + offset >= max)
        obj->rect.left = 0;
    else
        obj->rect.left += offset;
    sfSprite_setTextureRect(obj->sprite, obj->rect);
}
