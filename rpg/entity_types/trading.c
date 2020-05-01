/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** trading.c
*/

#include <entitybase.h>
#include <data_storage.h>
#include <internal_data.h>
#include <player.h>
#include <menu.h>
#include <tools.h>
#include <item_list.h>
#include <event.h>
#include <trading.h>
#include <executor.h>
#include <pause.h>

static void build_trade_list(dynamic_list_t *self)
{
    trade_list_t *new = NULL;
    sfTexture *texture = get_from_dict(get_data_storage()->textures, "button");
    sfFont *font = get_internal_data()->text_font;
    pos_t pos = {{self->pos.v1.x + 16, self->pos.v1.y + 8},
        {self->pos.v2.x - 48, 48}};

    destroy_trade_list_content(self);
    for (item_t *item = self->data; item; item = item->next) {
        new = malloc(sizeof(trade_list_t));
        *new = (trade_list_t) {create_button(texture, font, &pos, NULL),
            item->icon, sfText_create(), sfText_create(), self->local};
        set_trade_list_parameters(new, item, get_sitem_from_item(item));
        sfText_setFont(new->text, font);
        sfSprite_setPosition(new->icon, (sfVector2f) {pos.v1.x + 16,
            pos.v1.y + 8});
        sfText_setPosition(new->text, (sfVector2f) {pos.v1.x + pos.v2.x - 52,
            pos.v1.y + 16});
        self->local = new;
        pos.v1.y += 64;
    }
}

void update_trade_list(dynamic_list_t *self, sfRenderWindow *window,
    data_storage_t *datas, sfVector2f *pos)
{
    static void *here = NULL;

    if (self->data != here)
        build_trade_list(self);
    sfRenderWindow_drawSprite(window, self->background, NULL);
    for (trade_list_t *item = self->local; item; item = item->next) {
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

char on_clic_trade_list(dynamic_list_t *self, sfVector2f *pos)
{
    trade_list_t *ilist = self->local;

    while (ilist) {
        if (ilist->button->pos.v1.x <= pos->x
            && ilist->button->pos.v2.x > pos->x
            && ilist->button->pos.v1.y <= pos->y
            && ilist->button->pos.v2.y > pos->y) {
            buy_this_item(get_data_storage()->player, ilist->button->data);
            return (1);
        }
        ilist = ilist->next;
    }
    return (0);
}

void trade_event(event_t *self, player_t *player)
{
    menu_t *menu;
    data_storage_t *datas = get_data_storage();

    if (!datas->key.space)
        return;
    (void) player;
    datas->key.space = 0;
    menu = (menu_t *) get_from_rec_dict(get_from_rec_dict(
        get_executor()->var, "menu"), "GUI");
    menu->dlist->data = self->tag;
    open_sub_menu(menu);
    reset_timers(get_data_storage(), NULL);
}