/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** item_list.c
*/

#include <entitybase.h>
#include <data_storage.h>
#include <internal_data.h>
#include <player.h>
#include <menu.h>
#include <tools.h>
#include <item_list.h>
#include <executor.h>
#include <pause.h>

void destroy_item_list_content(dynamic_list_t *self)
{
    item_list_t *tmp = self->local;

    while (tmp != NULL) {
        self->local = tmp->next;
        sfSprite_destroy(tmp->button->display[0]);
        sfSprite_destroy(tmp->button->display[1]);
        sfSprite_destroy(tmp->button->display[2]);
        sfText_destroy(tmp->button->text);
        free(tmp->button);
        sfText_destroy(tmp->text);
        free(tmp);
        tmp = self->local;
    }
}

void update_item_list(dynamic_list_t *self, sfRenderWindow *window,
    data_storage_t *datas, sfVector2f *pos)
{
    static void *here = NULL;

    if (self->data != here)
        build_item_list(self);
    for (item_list_t *item = self->local; item; item = item->next) {
        if (item->button->pos.v1.x <= pos->x && item->button->pos.v2.x > pos->x
            && item->button->pos.v1.y <= pos->y
            && item->button->pos.v2.y > pos->y) {
            sfRenderWindow_drawSprite(window,
                item->button->display[1 + datas->mouse.left], NULL);
        } else
            sfRenderWindow_drawSprite(window, *item->button->display, NULL);
        sfRenderWindow_drawText(window, item->button->text, NULL);
        sfRenderWindow_drawSprite(window, item->icon, NULL);
        sfRenderWindow_drawText(window, item->text, NULL);
    }
}

char on_clic_item_list(dynamic_list_t *self, sfVector2f *pos)
{
    item_list_t *ilist = self->local;

    while (ilist) {
        if (ilist->button->pos.v1.x <= pos->x
            && ilist->button->pos.v2.x > pos->x
            && ilist->button->pos.v1.y <= pos->y
            && ilist->button->pos.v2.y > pos->y) {
            consume_item_from_inventory(ilist->button->data, ilist->text);
            return (1);
        }
        ilist = ilist->next;
    }
    return (0);
}

void open_inventory(data_storage_t *datas)
{
    menu_t *menu = (menu_t *) get_from_rec_dict(get_from_rec_dict(
        get_executor()->var, "menu"), "GUI");

    menu->dlist->data = datas->player->inventory->next;
    open_sub_menu(menu);
    reset_timers(datas, NULL);
}

void close_menu(menu_t *menu)
{
    menu->opened = 0;
}
