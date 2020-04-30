/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** item_list.h
*/

#ifndef ITEM_LIST_H_
#define ITEM_LIST_H_

typedef struct item_list {
    button_t *button;
    sfSprite *icon;
    sfText *text;
    struct item_list *next;
} item_list_t;

void consume_item_from_inventory(sitem_t *item, sfText *amount);
char on_clic_item_list(dynamic_list_t *self, sfVector2f *pos);
void update_item_list(dynamic_list_t *self, sfRenderWindow *window,
    data_storage_t *datas, sfVector2f *pos);
void open_inventory(data_storage_t *datas);

static inline void update_text_value(long value, sfText *amount)
{
    static char buffer[16];
    char *ptr = buffer + 15;

    buffer[15] = '\0';
    if (value == 0)
        *(--ptr) = '0';
    while (value > 0) {
        *(--ptr) = '0' + value % 10;
        value /= 10;
    }
    sfText_setString(amount, ptr);
}

static inline void set_item_list_parameters(item_list_t *new, sitem_t *item)
{
    new->button->data = item;
    new->icon = item->item->icon;
    sfText_setString(new->button->text, tmpcat("     ", item->item->name));
    sfText_setFillColor(new->text, sfBlack);
    sfText_setCharacterSize(new->text, 16);
    update_text_value(item->amount, new->text);
}

#endif /* ITEM_LIST_H_ */
