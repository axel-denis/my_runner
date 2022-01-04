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

sfRenderWindow *create_window(void)
{
    sfVideoMode video_mode;
    sfRenderWindow *window;

    video_mode.width = WIDTH;
    video_mode.height = HEIGHT;
    video_mode.bitsPerPixel = 32;
    window = sfRenderWindow_create(video_mode, "RABBIT",
    sfDefaultStyle | sfClose | sfResize, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    return window;
}

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

int map_len(char *buffer)
{
    int i = 0;
    while (buffer[i] != '|')
        i += 1;
    return i / CHUNK;
}

map_info *map_creator(void)
{
    map_info *map = malloc(sizeof(map_info));

    map->buffer = read_map_file("map.txt");
    map->texture = sfTexture_createFromFile("./assets/Tiles.psd", NULL);
    map->bg = new_mountain();
    map->len = map_len(map->buffer);
    map->data = map_init(map->buffer, map->len, map->texture);
    map->iteration = 60; //60 étant la longueur de map_init
}

void main(void)
{
    map_info *map = map_creator();
    sfEvent event;
    sfRenderWindow *window = create_window();
    sfVector2f testpos;
    sfClock *clock = sfClock_create();
    sfTime time;
    float seconds;
    gameobj *obj = new_duck("assets/sprite.png", testpos);

    while (sfRenderWindow_isOpen(window)) {
        map_col *test = map->data;
        sfRenderWindow_clear(window, sfBlack);
        while (test != NULL) {
            for (int i = 0; i < MAP_HEIGHT; i++)
                sfRenderWindow_drawSprite(window, test->col[i].sprite, NULL);
            test = test->next;
        }
        move_blocks(1, 5, map);
        sfRenderWindow_drawSprite(window, obj->sprite, NULL);
        time = sfClock_getElapsedTime(clock);
        seconds = time.microseconds / 1000000.0;
        //display_parallax(bg, window);
        sfRenderWindow_display(window);
        if (seconds >= .2) {
            animate(obj, 110, 330);
            sfClock_restart(clock);
        }
        while(sfRenderWindow_pollEvent(window, &event))
            event_handeling(event, window, obj);
    }
    free_map(map);
}

void free_parallax(parallax *bg)
{
    if (bg->next != NULL)
        free_parallax(bg->next);
    sfSprite_destroy(bg->sprite);
    free(bg);
}

void free_map(map_info *map)
{
    free(map->buffer);
    free_col(map->data);
    free_parallax(map->bg);
    sfTexture_destroy(map->texture);
    free(map);
}
