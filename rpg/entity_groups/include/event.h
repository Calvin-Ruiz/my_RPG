/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** event.h
*/

#ifndef EVENT_H_
#define EVENT_H_

#include <executor.h>

typedef struct event {
    struct event *next;
    struct event *prev;
    struct entity *disp_next;
    sfSprite **sprite;
    ushort_t *size;
    long long timer;
    long long frame_delay;
    uchar_t frame;
    uchar_t frame_dec;
    ushort_t id;
    int health;
    float speed;
    pos_t pos;
    void (*update)(struct event *self, int delta_time);
    void *(*new)();
    void (*destroy)(struct event *self);
    void *(*load)();
    void (*save)();
    void (*event)(struct event *self, player_t *player);
    char *command_name;
    ushort_t tag_id;
    void *tag;
} event_t;

#ifndef CALLER
#define CALLER
    typedef struct caller {
        long nb_args;
        void (*caller)(char **);
        char *function_name;
        void *self;
        player_t *player;
    } caller_t;
#endif /* CALLER */

void event_update(entitylist_t *self, player_t *player);

static inline void event_event(event_t *self, player_t *player)
{
    if (self->event)
        self->event(self, player);
    else
        call_function(((char **) &(caller_t) {4, call_function,
            self->command_name, self, player}) + 1);
}

#endif /* EVENT_H_ */
