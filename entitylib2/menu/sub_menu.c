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
    sfVector2f vs = sfView_getSize(menu->view);
    sfTexture *texture = sfTexture_create(size.x, size.y);
    sfSprite *back = sfSprite_create();

    menu->opened = 1;
    if (texture && back) {
        sfTexture_updateFromRenderWindow(texture, menu->window, 0, 0);
        sfSprite_setTexture(back, texture, sfTrue);
        sfSprite_setScale(back, (sfVector2f) {vs.x / size.x , vs.y / size.y});
    }
    while (menu->opened) {
        sfRenderWindow_setView(menu->window, menu->view);
        sfRenderWindow_drawSprite(menu->window, back, NULL);
        menu_update(menu, datas);
        menu_events(menu, datas);
    }
    sfTexture_destroy(texture);
    sfSprite_destroy(back);
}

void destroy_menu(menu_t *menu)
{
    if (menu->background)
        sfSprite_destroy(menu->background);
    if (menu->view)
        sfView_destroy(menu->view);
    destroy_button_array(menu->button);
    destroy_image_array(menu->images);
    destroy_text_array(menu->text);
    destroy_dynamic_text_array(menu->dtext);
    free(menu);
}
