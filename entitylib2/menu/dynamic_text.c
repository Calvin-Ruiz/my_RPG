/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** dynamic_text.c
*/

#include <entitybase.h>
#include <data_storage.h>
#include <internal_data.h>
#include <menu.h>

void create_dynamic_text_cmd(char **arr)
{
    dynamic_text_t *dtext = malloc(sizeof(dynamic_text_t));

    if (dtext == NULL)
        return;
    *dtext = (dynamic_text_t) {((menu_t *) arr[1])->dtext, sfText_create(),
        (sfVector2f) {(long) arr[2], (long) arr[3]}, arr[4], NULL,
        (void (*)(dynamic_text_t *)) arr[5]};
    if (dtext->text == NULL)
        return;
    sfText_setFont(dtext->text, get_internal_data()->text_font);
    sfText_setPosition(dtext->text, dtext->pos);
    sfText_setFillColor(dtext->text, *(sfColor *) (arr + 6));
    sfText_setCharacterSize(dtext->text, (long) arr[7]);
    ((menu_t *) arr[1])->dtext = dtext;
}

void update_dynamic_text_from_int(dynamic_text_t *self)
{
    static char buffer[16];
    char *ptr = buffer + 15;
    int tmp;

    if (*(int *) self->data == 0)
        sfText_setString(self->text, "0");
    if (*(int *) self->data == (long) self->last)
        return;
    self->last = (void *) (long) *(int *) self->data;
    buffer[15] = '\0';
    tmp = *(int *) self->data;
    while (tmp > 0) {
        *(--ptr) = '0' + tmp % 10;
        tmp /= 10;
    }
    sfText_setString(self->text, ptr);
}

static char *vec2i_to_str(sfVector2i *vec)
{
    static char buffer[32];
    char *ptr = buffer + 30;
    sfVector2i tmp = *vec;

    buffer[31] = '\0';
    while (tmp.y > 0) {
        *(ptr--) = '0' + tmp.y % 10;
        tmp.y /= 10;
    }
    *(ptr--) = '/';
    if (tmp.x == 0)
        *(ptr--) = '0';
    while (tmp.x > 0) {
        *(ptr--) = '0' + tmp.x % 10;
        tmp.x /= 10;
    }
    return (ptr);
}

void update_dynamic_text_from_2int(dynamic_text_t *self)
{
    if (*(long *) self->data == (long) self->last)
        return;
    self->last = (void *) *(long *) self->data;
    sfText_setString(self->text, vec2i_to_str(self->data) + 1);
}

void update_dynamic_text_array(sfRenderWindow *window, dynamic_text_t *dtext)
{
    while (dtext) {
        dtext->update(dtext);
        sfRenderWindow_drawText(window, dtext->text, NULL);
        dtext = dtext->next;
    }
}
