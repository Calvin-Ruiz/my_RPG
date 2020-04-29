/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** text.c
*/

#include <entitybase.h>
#include <data_storage.h>
#include <internal_data.h>
#include <menu.h>

void create_text_cmd(char **arr)
{
    text_t *text = malloc(sizeof(text_t));

    if (text == NULL)
        return;
    *text = (text_t) {((menu_t *) arr[1])->text, sfText_create(),
        (sfVector2f) {(long) arr[2], (long) arr[3]}};
    if (text->text == NULL)
        return;
    sfText_setFont(text->text, get_internal_data()->text_font);
    sfText_setPosition(text->text, text->pos);
    for (u_char i = -1; arr[4][++i] != '\0';) {
        if (arr[4][i] == '_')
            arr[4][i] = ' ';
    }
    sfText_setString(text->text, arr[4]);
    sfText_setFillColor(text->text, *(sfColor *) (arr + 5));
    sfText_setCharacterSize(text->text, (long) arr[6]);
    ((menu_t *) arr[1])->text = text;
}

void update_text_array(sfRenderWindow *window, text_t *text)
{
    while (text) {
        sfRenderWindow_drawText(window, text->text, NULL);
        text = text->next;
    }
}
