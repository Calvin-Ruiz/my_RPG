/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** event.h
*/

#ifndef EVENT_H_
#define EVENT_H_

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
    void (*destroy)();
    void *(*load)();
    void (*save)();
    void (*event)(struct event *self, player_t *player);
    ushort_t tag_id;
    void *tag;
} event_t;

void event_update(entitylist_t *self, player_t *player);

#endif /* EVENT_H_ */
