/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** main.c
*/

#include "includes/csfml.h"
#include "includes/consts.h"
#include "includes/structs.h"

void event_handeling(sfEvent event, sfRenderWindow *window)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
        sfRenderWindow_close(window);
}

void main(void)
{
    sfEvent event;
    sfRenderWindow *window;
    sfVideoMode video_mode;
    sfVector2f testpos;

    video_mode.width = WIDTH;
    video_mode.height = HEIGHT;
    video_mode.bitsPerPixel = 32;
    window = sfRenderWindow_create(video_mode, "RABBIT",
    sfDefaultStyle | sfClose | sfResize, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    gameobj *obj = new_duck("sprite.png", testpos);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_drawSprite(window, obj->sprite, NULL);
        sfRenderWindow_display(window);
        while(sfRenderWindow_pollEvent(window, &event))
            event_handeling(event, window);
    }
}
