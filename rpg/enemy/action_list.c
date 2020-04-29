/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** action_list.c
*/
#include <entitybase.h>
#include <data_storage.h>
#include <internal_data.h>
#include <menu.h>
#include <action_list.h>

static void build_capacity_selection(dynamic_list_t *self,
    data_storage_t *datas)
{
    capacity_t *cap = *(capacity_t **) self->data;
    sfTexture *texture = get_from_dict(datas->textures, "button");
    sfFont *font = get_internal_data()->text_font;
    pos_t pos = (pos_t) {(sfVector2f) {self->pos.v1.x + 16,
        self->pos.v1.y + 16}, (sfVector2f) {self->pos.v2.x - 40, 32}};
    button_t *button = NULL;

    sfSprite_setPosition(self->background, self->pos.v1);
    while (cap) {
        button = create_button(texture, font, &pos, use_capacity);
        sfText_setString(button->text, "attack");
        button->data = cap;
        button->next = self->local;
        self->local = button;
        pos.v1.x += 48;
        cap = cap->next;
    }
}

void update_capacity_selection(dynamic_list_t *self, sfRenderWindow *window,
    data_storage_t *datas, sfVector2f *mouse)
{
    if (self->local == NULL)
        build_capacity_selection(self, datas);
    sfRenderWindow_drawSprite(window, self->background, NULL);
    update_button_array(window, self->local, &datas->mouse, mouse);
}

char action_list_clic(dynamic_list_t *self, sfVector2f *pos)
{
    return (button_clic(self->local, pos));
}
