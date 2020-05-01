/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** button.c
*/

#include <entitybase.h>
#include <data_storage.h>
#include <menu.h>

static char create_button_sprite(button_t *new, sfTexture *texture, pos_t *pos)
{
    sfVector2u size = sfTexture_getSize(texture);
    sfIntRect rect = {0, 0, size.x, size.y / 3};

    *new->display = sfSprite_create();
    if (*new->display == NULL)
        return (1);
    sfSprite_setTexture(*new->display, texture, sfFalse);
    sfSprite_setPosition(*new->display, pos->v1);
    sfSprite_setScale(*new->display, (sfVector2f) {pos->v2.x / (float) size.x,
        pos->v2.y / (float) rect.height});
    sfSprite_setTextureRect(*new->display, rect);
    rect.top += rect.height;
    new->display[1] = sfSprite_copy(*new->display);
    new->display[2] = sfSprite_copy(*new->display);
    if (new->display[1] == NULL || new->display[2] == NULL)
        return (1);
    sfSprite_setTextureRect(new->display[1], rect);
    rect.top += rect.height;
    sfSprite_setTextureRect(new->display[2], rect);
    return (0);
}

button_t *create_button(sfTexture *texture, sfFont *font, pos_t *pos,
    void (*press_action)(void *data))
{
    button_t *new = malloc(sizeof(button_t));

    if (new == NULL || create_button_sprite(new, texture, pos))
        return (NULL);
    new->text = sfText_create();
    sfText_setFont(new->text, font);
    sfText_setPosition(new->text,
        (sfVector2f) {pos->v1.x + 16, pos->v1.y + 16});
    sfText_setCharacterSize(new->text, 12);
    sfText_setFillColor(new->text, sfBlack);
    new->data = NULL;
    new->press_action = press_action;
    new->pos.v1 = pos->v1;
    new->pos.v2.x = pos->v1.x + pos->v2.x;
    new->pos.v2.y = pos->v1.y + pos->v2.y;
    return (new);
}

void update_button_array(sfRenderWindow *window, button_t *button,
    my_mouse_t *mouse, sfVector2f *pos)
{
    while (button) {
        if (button->pos.v1.x <= pos->x && button->pos.v2.x > pos->x
            && button->pos.v1.y <= pos->y && button->pos.v2.y > pos->y) {
            sfRenderWindow_drawSprite(window, button->display[1 + mouse->left],
                NULL);
        } else
            sfRenderWindow_drawSprite(window, *button->display, NULL);
        sfRenderWindow_drawText(window, button->text, NULL);
        button = button->next;
    }
}

char button_clic(button_t *button, sfVector2f *pos)
{
    while (button) {
        if (button->pos.v1.x <= pos->x && button->pos.v2.x > pos->x
            && button->pos.v1.y <= pos->y && button->pos.v2.y > pos->y) {
            button->press_action(button->data);
            return (1);
        }
        button = button->next;
    }
    return (0);
}

void destroy_button_array(button_t *button)
{
    button_t *tmp = NULL;

    while (button) {
        tmp = button;
        button = button->next;
        sfSprite_destroy(tmp->display[0]);
        sfSprite_destroy(tmp->display[1]);
        sfSprite_destroy(tmp->display[2]);
        sfText_destroy(tmp->text);
        free(tmp);
    }
}
