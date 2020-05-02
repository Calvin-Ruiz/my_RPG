/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** dynamic_list.c
*/

#include <entitybase.h>
#include <data_storage.h>
#include <menu.h>

void create_dynamic_list_cmd(char **arr)
{
    dynamic_list_t *new = malloc(sizeof(dynamic_list_t));
    sfVector2u size = sfTexture_getSize((sfTexture *) arr[2]);

    new->background = sfSprite_create();
    new->pos = *(pos_t *) arr[3];
    new->local = NULL;
    new->data = arr[4];
    new->update = (void (*)(struct dlist *self, sfRenderWindow *window,
        data_storage_t *datas, sfVector2f *mouse)) arr[5];
    new->on_clic = (char (*)(struct dlist *self, sfVector2f *pos)) arr[6];
    new->destroy_local = (void (*) (struct dlist *self)) arr[7];
    new->view = sfView_copy(((menu_t *) arr[1])->view);
    new->center = sfView_getCenter(new->view);
    sfSprite_setTexture(new->background, (sfTexture *) arr[2], sfTrue);
    sfSprite_setPosition(new->background, new->pos.v1);
    sfSprite_setScale(new->background,
        (sfVector2f) {new->pos.v2.x / (float) size.x,
        new->pos.v2.y / (float) size.y});
    new->next = ((menu_t *) arr[1])->dlist;
    ((menu_t *) arr[1])->dlist = new;
}

char dynamic_list_clic(menu_t *menu, sfVector2f *pos)
{
    dynamic_list_t *dlist = menu->dlist;

    while (dlist) {
        if (dlist->on_clic && dlist->on_clic(dlist, pos))
            return (1);
        dlist = dlist->next;
    }
    return (0);
}

void dynamic_list_scroll(menu_t *menu, char delta)
{
    sfVector2f center = sfView_getCenter(menu->view);
    dynamic_list_t *dlist = menu->dlist;

    while (dlist) {
        dlist->center.y -= delta * 64;
        if (dlist->center.y < center.y)
            dlist->center.y = center.y;
        sfView_setCenter(dlist->view, dlist->center);
        dlist = dlist->next;
    }
}

void destroy_dynamic_list(dynamic_list_t *self)
{
    dynamic_list_t *tmp = NULL;

    while (self) {
        tmp = self->next;
        if (self->destroy_local)
            self->destroy_local(self);
        sfSprite_destroy(self->background);
        sfView_destroy(self->view);
        free(self);
        self = tmp;
    }
}
