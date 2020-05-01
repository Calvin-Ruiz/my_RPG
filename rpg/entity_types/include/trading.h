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

static inline void set_trade_list_parameters(trade_list_t *new, item_t *item,
    sitem_t *sitem)
{
    new->button->data = item;
    new->icon = item->icon;
    sfText_setString(new->button->text, tmpcat("     ", item->name));
    sfText_setFillColor(new->text, sfBlack);
    sfText_setCharacterSize(new->text, 16);
    update_text_value(sitem ? sitem->amount : 0, new->text);
    sfText_setFillColor(new->amount, sfBlack);
    sfText_setCharacterSize(new->amount, 16);
    update_text_value(item->cost, new->amount);
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

static inline sitem_t *get_sitem_from_item(item_t *item)
{
    sitem_t *sitem = get_data_storage()->player->inventory->next;

    while (sitem) {
        if (sitem->item == item)
            return (sitem);
        sitem = sitem->next;
    }
    return (NULL);
}

void update_trade_list(dynamic_list_t *self, sfRenderWindow *window,
    data_storage_t *datas, sfVector2f *pos);
char on_clic_trade_list(dynamic_list_t *self, sfVector2f *pos);
void trade_event(event_t *self, player_t *player);

#endif /* TRADING_H_ */
