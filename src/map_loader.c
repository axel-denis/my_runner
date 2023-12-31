/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** loaders.c
*/

#include "../includes/csfml.h"
#include "../includes/consts.h"
#include "../includes/structs.h"
#include "../includes/lib.h"
#include "../includes/utils.h"
#include "../includes/loaders.h"
#include "../includes/effects.h"

char *read_map_file(char *map_file)
{
    int fd = open(map_file, O_RDONLY);
    char *buffer = malloc(sizeof(char) * 1000000);

    if (fd == -1) {
        my_putstr("can't read this file!\n");
        return NULL;
    }
    read(fd, buffer, 1000000);
    close(fd);
    return buffer;
}

map_col *map_col_reader(char *buffer, int x, int map_len, sfTexture *texture, \
    float last_pos)
{
    map_col *actual = malloc(sizeof(map_col));

    actual->col = malloc(sizeof(block) * MAP_HEIGHT);
    actual->next = NULL;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        if (x >= INITIAL_MAP_WIDTH)
            actual->col[i].pos.x = 32 * INITIAL_MAP_WIDTH + last_pos - 1;
        else
            actual->col[i].pos.x = x * 32;
        actual->col[i].pos.y = i * 32;
        actual->col[i].type = (int) (buffer[(x * CHUNK) + \
            ((map_len * CHUNK + 2) * i)] - '0');
        if (actual->col[i].type + '0' == '|')
            return NULL;
        actual->col[i].sprite = block_sprite(actual->col[i].type, texture);
        set_effect(actual, actual->col[i].pos, i);
    }
    return actual;
}

map_col *map_init(char *buffer, int map_len, sfTexture *texture)
{
    map_col *temp_node = NULL;
    map_col *new_temp_node = NULL;

    for (int index = 0; index < INITIAL_MAP_WIDTH; index++) {
        new_temp_node = map_col_reader(buffer, index, map_len, texture, 0.0);
        new_temp_node->next = temp_node;
        temp_node = new_temp_node;
    }
    return temp_node;
}

map_info *map_loader(map_info *map)
{
    sfVector2f pos = {600, 0};

    map->texture = sfTexture_createFromFile("./assets/tiles.png", NULL);
    map->bg = new_mountain();
    map->len = map_len(map->buffer);
    map->data = map_init(map->buffer, map->len, map->texture);
    map->iteration = INITIAL_MAP_WIDTH;
    map->clock = sfClock_create();
    map->text.font = sfFont_createFromFile("assets/fonts/arcadefont.ttf");
    map->text.text = create_text("RABBIT RUNNER", 100, pos, map->text.font);
    map->text.pos = pos;
    return map;
}

map_info *map_creator(map_info *map, char *path)
{
    map->buffer = read_map_file(path);
    if (map_check(map->buffer) == 1)
        return NULL;
    map->sounds[0] = sfMusic_createFromFile("assets/audio/main_menu.ogg");
    sfMusic_setLoop(map->sounds[0], sfTrue);
    sfMusic_setVolume(map->sounds[0], 40);
    map->sounds[1] = sfMusic_createFromFile("assets/audio/main_game.ogg");
    sfMusic_setLoop(map->sounds[1], sfTrue);
    sfMusic_setVolume(map->sounds[1], 40);
    map->sounds[2] = sfMusic_createFromFile("assets/audio/jump.ogg");
    return map_loader(map);
}
