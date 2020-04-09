/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** main.c
*/
#include <main.h>
#include <events.h>
#include <entity_display.h>
#include <etools.h>

void my_closure(data_storage_t *datas)
{
    sfRenderWindow_close(datas->window);
    datas->on_mainloop = 0;
    ((menu_t *) datas->main_menu)->opened = 0;
    ((menu_t *) datas->pause_menu)->opened = 0;
    datas->is_alive = 0;
    free_storage_content(datas, 7);
}

void my_event(data_storage_t *datas)
{
    sfEvent event;

    while (datas->on_mainloop &&
        sfRenderWindow_pollEvent(datas->window, &event)) {
        if (event.type == sfEvtClosed) {
            my_closure(datas);
            return;
        }
        if (event.type == sfEvtKeyPressed)
            event_press(datas, event.key.code);
        if (event.type == sfEvtKeyReleased)
            event_release(datas, event.key.code);
        if (event.type == sfEvtMouseButtonPressed)
            mouse_clic(datas, &event.mouseButton);
        if (event.type == sfEvtMouseButtonReleased)
            mouse_release(datas, &event.mouseButton);
        if (event.type == sfEvtMouseWheelScrolled)
            event_scroll(datas, event.mouseWheelScroll.delta);
    }
}

void mainloop(data_storage_t *datas, sfRenderWindow *window)
{
    long long last = sfClock_getElapsedTime(datas->clock).microseconds;
    long long actual = last;

    while (datas->on_mainloop) {
        actual = sfClock_getElapsedTime(datas->clock).microseconds;
        datas->player->update(datas->player, (u_int) 25000, &datas->key);
        srand(actual);
        last += 25000;
        if (actual < last)
            sfSleep((sfTime) {last - actual});
        display_entities(window, &(*datas->entitylists)->next);
        update_window(window, datas);
        my_event(datas);
    }
}

int main(void)
{
    data_storage_t *datas = init_data_storage(NB_ENTITYLIST);

    if (init_textures(datas) || init_sounds(datas) ||
        create_window((sfVideoMode) {800, 600, 32}, "My RPG",
        sfResize | sfClose, 60))
        return (84);
    init_some_datas(datas);
    init_executor();
    open_menu(datas->main_menu);
    return (0);
}
