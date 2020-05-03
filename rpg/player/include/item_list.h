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
void open_fight_inventory(data_storage_t *datas);
void close_menu(menu_t *menu);
void buy_this_item(player_t *player, item_t *item);
void destroy_item_list_content(dynamic_list_t *self);

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
    sfText_setFillColor(new->text, sfBlue);
    sfText_setCharacterSize(new->text, 16);
    update_text_value(item->amount, new->text);
}

static inline void build_item_list(dynamic_list_t *self)
{
    item_list_t *new = NULL;
    sfTexture *texture = get_from_dict(get_data_storage()->textures, "button");
    sfFont *font = get_internal_data()->text_font;
    pos_t pos = {{self->pos.v1.x + 16, self->pos.v1.y + 20},
        {self->pos.v2.x - 48, 48}};

    destroy_item_list_content(self);
    for (sitem_t *item = self->data; item; item = item->next) {
        new = malloc(sizeof(item_list_t));
        *new = (item_list_t) {create_button(texture, font, &pos, NULL),
            item->item->icon, sfText_create(), self->local};
        set_item_list_parameters(new, item);
        sfText_setFont(new->text, font);
        sfSprite_setPosition(new->icon, (sfVector2f) {pos.v1.x + 16,
            pos.v1.y + 8});
        sfText_setPosition(new->text, (sfVector2f) {pos.v1.x + pos.v2.x - 52,
            pos.v1.y + 16});
        self->local = new;
        pos.v1.y += 64;
    }
}

static inline void destroy_items(item_t *item)
{
    item_t *tmp = NULL;

    while (item) {
        tmp = item->next;
        sfSprite_destroy(item->icon);
        free(item->name);
        free(item);
        item = tmp;
    }
}

#endif /* ITEM_LIST_H_ */
