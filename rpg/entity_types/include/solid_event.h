/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** solid_event.h
*/

#ifndef SOLID_EVENT_H_
#define SOLID_EVENT_H_

#include <event.h>

typedef struct solid_event_save {
    sfVector2f pos;
    uchar_t frame_dec;
    uchar_t frame;
    ushort_t tag_id;
} event_save_t;

void create_event_cmd(char **arr);
event_t *new_solid_event(char **arr);
void default_event_update(event_t *self, int delta_time);
void destroy_event(event_t *self);
event_t *load_solid_event(event_t *self, int fd);
void save_solid_event(event_t *self, int fd);

#endif /* SOLID_EVENT_H_ */
