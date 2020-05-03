/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** events.h
*/

#ifndef EVENTS_H_
#define EVENTS_H_

static inline void event_press(data_storage_t *datas, sfKeyCode code,
    long long *last)
{
    if (code == sfKeyF10)
        datas->ask_command = 1;
    if (code == sfKeyF12)
        my_take_screenshoot(datas->window);
    if (code == sfKeyLeft)
        datas->key.left = 1;
    if (code == sfKeyRight)
        datas->key.right = 1;
    if (code == sfKeyUp)
        datas->key.up = 1;
    if (code == sfKeyDown)
        datas->key.down = 1;
    if (code == sfKeySpace)
        datas->key.space = 1;
    if (code == sfKeyEscape) {
        open_sub_menu(datas->pause_menu);
        reset_timers(datas, last);
    }
    if (code == sfKeyI)
        open_inventory(datas);
}

static inline void event_release(data_storage_t *datas, sfKeyCode code)
{
    if (code == sfKeyLeft)
        datas->key.left = 0;
    if (code == sfKeyRight)
        datas->key.right = 0;
    if (code == sfKeyUp)
        datas->key.up = 0;
    if (code == sfKeyDown)
        datas->key.down = 0;
    if (code == sfKeySpace)
        datas->key.space = 0;
}

static inline void mouse_clic(data_storage_t *datas, sfMouseButtonEvent *mouse)
{
    switch (mouse->button) {
        case sfMouseLeft:
            datas->mouse.left = 1;
            return;
        case sfMouseRight:
            datas->mouse.right = 1;
            mouse_edit(datas, mouse, 0);
            return;
        case sfMouseMiddle:
            datas->mouse.wheel = 1;
            return;
        default:
            return;
    }
}

static inline void mouse_release(data_storage_t *datas,
    sfMouseButtonEvent *mouse)
{
    switch (mouse->button) {
        case sfMouseLeft:
            datas->mouse.left = 0;
            return;
        case sfMouseRight:
            datas->mouse.right = 0;
            return;
        case sfMouseMiddle:
            datas->mouse.wheel = 0;
            return;
        default:
            return;
    }
}

static inline void event_scroll(data_storage_t *datas, float delta)
{
    mouse_edit(datas, NULL, delta);
}

#endif /* EVENTS_H_ */
