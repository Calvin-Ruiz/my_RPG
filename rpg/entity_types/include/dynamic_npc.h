/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** dynamic_npc.h
*/

#ifndef DYNAMIC_NPC_H_
#define DYNAMIC_NPC_H_

#include <npc.h>

void create_way_cmd(char **arr);
void create_npc_cmd(char **arr);
void default_npc_update(npc_t *self, int delta_time);
void destroy_npc(npc_t *self);
npc_t *new_npc(char **arr);

static inline void move_npc(npc_t *self)
{
    sfVector2f mv = {self->way->pos.x - self->pos.v1.x,
        self->way->pos.y - self->pos.v1.y};
    sfVector2f length = {mv.x * mv.x, mv.y * mv.y};
    if (length.x <= length.y) {
        self->frame_dec = (mv.y >= 0) ? self->size[2] : self->size[2] * 3;
        if (length.x * 12 > length.y) {
            self->pos.v1.x += ((mv.x < 0) ? -self->speed : self->speed) * 0.7f;
            self->pos.v1.y += ((mv.y < 0) ? -self->speed : self->speed) * 0.7f;
        } else
            self->pos.v1.y += (mv.y < 0) ? -self->speed : self->speed;
    } else {
        self->frame_dec = (mv.x > 0) ? 0 : self->size[2] << 1;
        if (length.y * 12 > length.x) {
            self->pos.v1.x += ((mv.x < 0) ? -self->speed : self->speed) * 0.7f;
            self->pos.v1.y += ((mv.y < 0) ? -self->speed : self->speed) * 0.7f;
        } else
            self->pos.v1.x += (mv.x < 0) ? -self->speed : self->speed;
    }
    if (length.x + length.y <= self->speed)
        self->pos.v1 = self->way->pos;
}

#endif /* DYNAMIC_NPC_H_ */
