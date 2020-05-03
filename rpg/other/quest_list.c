/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** quest_list.c
*/
#include <entitybase.h>
#include <data_storage.h>
#include <internal_data.h>
#include <player.h>
#include <menu.h>
#include <quest_list.h>
#include <quest.h>
#include <executor.h>
#include <pause.h>

void destroy_quest_list_content(dynamic_list_t *self)
{
    quest_list_t *tmp = self->local;
    req_list_t *req = NULL;

    while (tmp != NULL) {
        self->local = tmp->next;
        while (tmp->req) {
            req = tmp->req;
            tmp->req = req->next;
            destroy_dynamic_text_array(req->dtext);
            sfText_destroy(req->text);
            free(req);
        }
        sfSprite_destroy(tmp->image->image);
        free(tmp->image);
        sfText_destroy(tmp->desc);
        free(tmp);
        tmp = self->local;
    }
}

static void build_quest_list(dynamic_list_t *self)
{
    quest_list_t *new = NULL;
    data_storage_t *datas = get_data_storage();
    sfTexture *texture = get_from_dict(datas->textures, "canvas");
    sfFont *font = get_internal_data()->text_font;
    pos_t pos = {{self->pos.v1.x + 16, self->pos.v1.y + 20},
        {self->pos.v2.x - 48, 48}};
    destroy_quest_list_content(self);
    for (dict_t *dict = self->data; dict; dict = dict->next) {
        new = malloc(sizeof(quest_list_t));
        *new = (quest_list_t) {create_image(texture, &pos), sfText_create(),
            NULL, self->local};
        if (!((quest_t *) dict->data)->success)
            sfSprite_setColor(new->image->image, (sfColor) {99, 99, 99, 255});
        sfText_setFont(new->desc, font);
        sfText_setString(new->desc, ((quest_t *) dict->data)->desc);
        sfText_setPosition(new->desc, (sfVector2f) {pos.v1.x + 16,
            pos.v1.y + 8});
        sfText_setCharacterSize(new->desc, 16);
        sfText_setFillColor(new->desc, sfBlack);
        self->local = new;
        pos.v1.y += 64;
    }
}

void update_quest_list(dynamic_list_t *self, sfRenderWindow *window,
    data_storage_t *datas, sfVector2f *pos)
{
    static void *here = NULL;

    (void) datas;
    (void) pos;
    if (self->data != here)
        build_quest_list(self);
    for (quest_list_t *item = self->local; item; item = item->next) {
        sfRenderWindow_drawSprite(window, item->image->image, NULL);
        sfRenderWindow_drawText(window, item->desc, NULL);
    }
}

void open_quest_menu(void *ptr)
{
    menu_t *menu = (menu_t *) get_from_rec_dict(get_from_rec_dict(
        get_executor()->var, "menu"), "quest");
    data_storage_t *datas = get_data_storage();

    (void) ptr;
    menu->dlist->data = datas->global[QUEST];
    open_sub_menu(menu);
    reset_timers(datas, NULL);
}
