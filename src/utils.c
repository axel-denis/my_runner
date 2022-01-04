/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** utils.c
*/

#include "../includes/csfml.h"
#include "../includes/consts.h"
#include "../includes/structs.h"
#include "../includes/lib.h"
#include "../includes/frees.h"

int map_len(char *buffer)
{
    int i = 0;
    while (buffer[i] != '|')
        i += 1;
    return i / CHUNK;
}

void set_tile_rectangle(sfSprite *sprite, int top, int left)
{
    sfIntRect rect = {top, left, 32, 32};
    sfSprite_setTextureRect(sprite, rect);
}

sfSprite *block_sprite(int type, sfTexture *blocks_texture)
{
    sfSprite *sprite = sfSprite_create();

    if (type >= 0 && type <= 6)
        sfSprite_setTexture(sprite, blocks_texture, sfTrue);
    if (type == 0)
        set_tile_rectangle(sprite, BLOCK_SIZE * 3, 0);
    if (type == 1)
        set_tile_rectangle(sprite, BLOCK_SIZE * 4, 0);
    if (type == 2)
        set_tile_rectangle(sprite, BLOCK_SIZE * 5, 0);
    if (type == 3)
        set_tile_rectangle(sprite, BLOCK_SIZE * 3, BLOCK_SIZE);
    if (type == 4)
        set_tile_rectangle(sprite, BLOCK_SIZE * 4, BLOCK_SIZE);
    if (type == 5)
        set_tile_rectangle(sprite, BLOCK_SIZE * 5, BLOCK_SIZE);
    if (type == 6)
        set_tile_rectangle(sprite, BLOCK_SIZE * 4, BLOCK_SIZE);
    return sprite;
}