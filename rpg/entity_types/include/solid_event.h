/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** solid_event.h
*/

#ifndef SOLID_EVENT_H_
#define SOLID_EVENT_H_

#include <event.h>

void create_event_cmd(char **arr);
event_t *new_solid_event(char **arr);
void default_event_update(event_t *self, int delta_time);
void destroy_event(event_t *self);

#endif /* SOLID_EVENT_H_ */
