/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** how_to_play.c
*/
#include <entitylib.h>
#include <htp.h>
#include <menu.h>

static void htp_scroll(data_storage_t *datas, htp_t *self, float delta)
{
    self->scroll -= delta * 32;
    if (self->scroll < 300)
        self->scroll = 300;
    if (self->scroll > 2100)
        self->scroll = 2100;
    sfView_setCenter(self->view, (sfVector2f) {400, self->scroll});
    sfRenderWindow_setView(datas->window, self->view);
}

static void htp_event(data_storage_t *datas, htp_t *self)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(datas->window, &event)) {
        if (event.type == sfEvtClosed || (event.type == sfEvtKeyPressed
            && event.key.code == sfKeyEscape)) {
            self->opened = 0;
            return;
        }
        if (event.type == sfEvtMouseWheelScrolled)
            htp_scroll(datas, self, event.mouseWheelScroll.delta);
    }
}

static void htp_menu(data_storage_t *datas)
{
    htp_t self = {sfView_copy(((menu_t *) datas->main_menu)->view), 300,
        sfSprite_create(), 1};

    if (self.view == NULL || self.background == NULL)
        return;
    sfSprite_setTexture(self.background, get_from_dict(datas->textures,
        "htp"), sfTrue);
    while (self.opened) {
        sfRenderWindow_drawSprite(datas->window, self.background, NULL);
        sfRenderWindow_display(datas->window);
        sfSleep((sfTime) {10000});
        htp_event(datas, &self);
    }
}

void init_htp_button(data_storage_t *datas)
{
    button_t *button = create_button((sfTexture *) sfSprite_getTexture(
        ((menu_t *) datas->main_menu)->button->display[0]),
        get_internal_data()->text_font, &(pos_t) {(sfVector2f) {272, 300},
        (sfVector2f) {256, 64}}, (void (*)(void *)) htp_menu);

    button->data = datas;
    button->next = ((menu_t *) datas->main_menu)->button;
    ((menu_t *) datas->main_menu)->button = button;
    sfText_setString(button->text, "How to Play");
}
