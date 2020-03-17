/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2019
** File description:
** pause.c
*/
#include <entitylib.h>
#include <menu.h>

void reset_timers(data_storage_t *datas, long long *last)
{
    uchar_t i = -1;

    while (++i < datas->nb_entitylist)
        datas->entitylists[i]->last = sfClock_getElapsedTime(
            datas->entitylists[i]->clock).microseconds;
    if (last)
        *last = sfClock_getElapsedTime(datas->clock).microseconds;
}

void exit_pause(data_storage_t *datas)
{
    ((menu_t *) datas->pause_menu)->opened = 0;
}

void exit_mainloop(data_storage_t *datas)
{
    ((menu_t *) datas->pause_menu)->opened = 0;
    datas->on_mainloop = 0;
}

void init_pause_buttons(menu_t *menu)
{
    data_storage_t *datas = get_data_storage();

    menu->button = create_button(get_from_dict(datas->texture_dict,
        "button.png"), get_internal_data()->text_font, (pos_t) {(sfVector2f)
        {272, 200}, (sfVector2f) {256, 64}}, (void (*)(void *)) exit_pause);
    menu->button->next = create_button(get_from_dict(datas->texture_dict,
        "button.png"), get_internal_data()->text_font, (pos_t) {(sfVector2f)
        {272, 300}, (sfVector2f) {256, 64}}, (void (*)(void *)) exit_mainloop);
    menu->button->next->next = create_button(get_from_dict(datas->texture_dict,
        "button.png"), get_internal_data()->text_font, (pos_t) {(sfVector2f)
        {272, 400}, (sfVector2f) {256, 64}}, (void (*)(void *)) my_closure);
    menu->button->next->next->next = NULL;
    menu->button->data = datas;
    menu->button->next->data = datas;
    menu->button->next->next->data = datas;
    sfText_setString(menu->button->text, "Resume");
    sfText_setString(menu->button->next->text, "Main menu");
    sfText_setString(menu->button->next->next->text, "Exit");
}
