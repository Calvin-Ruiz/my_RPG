/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** sub_menu.c
*/
#include <entitybase.h>
#include <data_storage.h>
#include <menu.h>

void open_sub_menu(menu_t *menu)
{
    data_storage_t *datas = get_data_storage();
    sfVector2u size = sfRenderWindow_getSize(menu->window);
    sfTexture *texture = sfTexture_create(size.x, size.y);

    menu->opened = 1;
    if (texture) {
        sfTexture_updateFromRenderWindow(texture, menu->window, 0, 0);
        sfSprite_setTexture(menu->background, texture, sfTrue);
    }
    while (menu->opened) {
        sfRenderWindow_drawSprite(menu->window, menu->background, NULL);
        menu_update(menu, datas);
        menu_events(menu, datas);
    }
    sfTexture_destroy(texture);
}
