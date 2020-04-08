/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** events.h
*/

#ifndef EVENTS_H_
#define EVENTS_H_

static inline void event_press(data_storage_t *datas, sfKeyCode code)
{
    (void) datas;
    (void) code;
}

static inline void event_release(data_storage_t *datas, sfKeyCode code)
{
    (void) datas;
    (void) code;
}

static inline void mouse_clic(data_storage_t *datas, sfMouseButtonEvent *mouse)
{
    switch (mouse->button) {
        case sfMouseLeft:
            datas->mouse.left = 1;
            return;
        case sfMouseRight:
            datas->mouse.right = 1;
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
    (void) datas;
    (void) delta;
}

#endif /* EVENTS_H_ */
