/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** trading.h
*/

#ifndef TRADING_H_
#define TRADING_H_

typedef struct trade_list {
    button_t *button;
    sfSprite *icon;
    sfText *text;
    sfText *amount;
    struct trade_list *next;
} trade_list_t;

static inline sitem_t *get_sitem_from_item(data_storage_t * const datas,
    item_t * const item)
{
    sitem_t *sitem = datas->player->inventory->next;

    while (sitem) {
        if (sitem->item == item)
            return (sitem);
        sitem = sitem->next;
    }
    return (NULL);
}

static inline void set_trade_list_parameters(trade_list_t * const new,
    item_t * const item, data_storage_t * const datas, const pos_t * const pos)
{
    sitem_t *sitem = get_sitem_from_item(datas, item);

    new->button->data = item;
    new->icon = item->icon;
    sfText_setString(new->button->text, tmpcat("     ", item->name));
    sfText_setFillColor(new->amount, sfBlue);
    sfText_setCharacterSize(new->amount, 16);
    update_text_value(sitem ? sitem->amount : 0, new->amount);
    sfText_setFillColor(new->text, sfBlack);
    sfText_setCharacterSize(new->text, 16);
    update_text_value(item->cost, new->text);
    sfSprite_setPosition(new->icon, (sfVector2f) {pos->v1.x + 16,
        pos->v1.y + 8});
    sfText_setPosition(new->text, (sfVector2f) {pos->v1.x + pos->v2.x - 96,
        pos->v1.y + 16});
    sfText_setPosition(new->amount, (sfVector2f) {pos->v1.x + pos->v2.x - 150,
        pos->v1.y + 16});
}

static inline void destroy_trade_list_content(dynamic_list_t *self)
{
    trade_list_t *tmp = self->local;

    while (tmp != NULL) {
        self->local = tmp->next;
        sfSprite_destroy(tmp->button->display[0]);
        sfSprite_destroy(tmp->button->display[1]);
        sfSprite_destroy(tmp->button->display[2]);
        sfText_destroy(tmp->button->text);
        free(tmp->button);
        sfText_destroy(tmp->text);
        sfText_destroy(tmp->amount);
        free(tmp);
        tmp = self->local;
    }
}

void update_trade_list(dynamic_list_t *self, sfRenderWindow *window,
    data_storage_t *datas, sfVector2f *pos);
char on_clic_trade_list(dynamic_list_t *self, sfVector2f *pos);
void trade_event(event_t *self, player_t *player);

#endif /* TRADING_H_ */
