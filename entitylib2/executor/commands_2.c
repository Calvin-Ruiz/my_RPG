/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** commands_2.c
*/

#include <executor.h>
#include <entitybase.h>
#include <data_storage.h>
#include <internal_data.h>
#include <menu.h>

void create_menu_cmd(char **arr)
{
    void **menus = get_ptr_from_dict((dict_t *) get_executor()->var, "menu");
    menu_t *menu = create_menu((sfRenderWindow *) arr[2], (sfTexture *) arr[3]);

    append_to_dict((dict_t **) menus, arr[1], menu);
}

void create_button_cmd(char **arr)
{
    button_t *button = create_button((sfTexture *) arr[2],
        get_internal_data()->text_font,
        (pos_t *) arr[3], (void (*)(void *)) arr[4]);

    sfText_setString(button->text, arr[5]);
    button->data = arr[6];
    button->next = ((menu_t *) arr[1])->button;
    ((menu_t *) arr[1])->button = button;
}

void use_capacity(void *data)
{
    get_data_storage()->global[ACTION] = data;
    ((menu_t *) get_from_rec_dict(get_from_rec_dict(get_executor()->var,
        "menu"), "fight"))->opened = 0;
}
