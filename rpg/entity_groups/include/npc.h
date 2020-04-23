/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** npc.h
*/

#ifndef NPC_H_
#define NPC_H_

#include <executor.h>
#include <basic_colliders.h>

typedef struct way {
    struct way *next;
    sfVector2f pos;
    short wait_time;
} way_t;

typedef struct npc {
    struct npc *next;
    struct npc *prev;
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
    void (*update)(struct npc *self, int delta_time);
    void *(*new)();
    void (*destroy)(struct npc *self);
    void *(*load)(struct npc *self, int fd);
    void (*save)();
    void (*event)(struct npc *self, player_t *player);
    char *command_name;
    ushort_t tag_id;
    void *tag;
    way_t *way;
    short wait_time;
} npc_t;

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

void npc_update(entitylist_t *self, player_t *player);

static inline void npc_collision(npc_t *self, player_t *player)
{
    dynamic_collide_force((entity_t *) self, (entity_t *) player);
    if (self->event)
        self->event(self, player);
    else
        call_function(((char **) &(caller_t) {4, call_function,
            self->command_name, self, player}) + 1);
}

#endif /* NPC_H_ */
