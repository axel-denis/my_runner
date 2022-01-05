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

char *read_map_file(char *map_file)
{
    int fd = open(map_file, O_RDONLY);
    char *buffer = malloc(sizeof(char) * 100000); // euh là pour le coup faudrait trouver mieux x)

    if (fd == -1) {
        my_putstr("can't read !\n");
        return NULL;
    }
    read(fd, buffer, 100000);
    close(fd);
    return buffer;
}

sfRenderWindow *create_window(void)
{
    sfVideoMode video_mode;
    sfRenderWindow *window;

    video_mode.width = WIDTH;
    video_mode.height = HEIGHT;
    video_mode.bitsPerPixel = 32;
    window = sfRenderWindow_create(video_mode, "RABBIT",
    sfDefaultStyle | sfClose | sfResize, NULL);
    sfRenderWindow_setFramerateLimit(window, 75);
    return window;
}

map_info *map_creator(void)
{
    map_info *map = malloc(sizeof(map_info));

    map->buffer = read_map_file("map.txt");
    map->texture = sfTexture_createFromFile("./assets/Tiles.psd", NULL);
    map->bg = new_mountain();
    map->len = map_len(map->buffer);
    map->data = map_init(map->buffer, map->len, map->texture);
    map->iteration = INITIAL_MAP_WIDTH;
    map->clock = sfClock_create();
    return map;
}

map_col *map_col_reader(char *buffer, int x, int map_len, sfTexture *texture,
                        float last_pos)
{
    map_col *actual = malloc(sizeof(map_col));
    int tmp_final_y = 0;

    actual->col = malloc(sizeof(block) * MAP_HEIGHT);
    actual->next = NULL;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        if (x >= INITIAL_MAP_WIDTH)
            actual->col[i].pos.x = 32 * INITIAL_MAP_WIDTH + last_pos - 1;
        else
            actual->col[i].pos.x = x * 32;
        actual->col[i].pos.y = i * 32;
        tmp_final_y = 0; //my_get_nbr(&buffer[(x * CHUNK) + ((map_len * CHUNK + 2) * i) + 1]);
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

    for (int index = 0; index < INITIAL_MAP_WIDTH; index++) {
        new_temp_node = map_col_reader(buffer, index, map_len, texture, 0.0);
        new_temp_node->next = temp_node;
        temp_node = new_temp_node;
    }
    return temp_node;
}
