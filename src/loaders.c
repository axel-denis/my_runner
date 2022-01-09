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

sfRenderWindow *create_window(void)
{
    sfVideoMode video_mode;
    sfRenderWindow *window;

    video_mode.width = WIDTH;
    video_mode.height = HEIGHT;
    video_mode.bitsPerPixel = 32;
    window = sfRenderWindow_create(video_mode, "RABBIT RUNNER",
    sfDefaultStyle | sfClose | sfResize, NULL);
    sfRenderWindow_setFramerateLimit(window, 75);
    return window;
}

int map_check(char *buffer)
{
    int lines_count = 0;
    int last_line_len = 0;
    int line_len = 0;

    if (buffer == NULL)
        return 1;
    for (int i = 0; buffer[i] != '\0'; i++) {
        line_len += 1;
        if (buffer[i] == '\n' && buffer[i - 1] == '|' && last_line_len != 0 \
            && line_len != last_line_len)
                return 1;
        else if (buffer[i] == '\n' && buffer[i - 1] == '|') {
            last_line_len = line_len;
            line_len = 0;
        }
        lines_count += (buffer[i] == '\n' && buffer[i - 1] == '|');
    }
    if (lines_count != MAP_HEIGHT)
        return 1;
    return 0;
}
