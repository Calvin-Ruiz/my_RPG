/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** basic_colliders.h
*/

#ifndef BASIC_COLLIDERS_H_
#define BASIC_COLLIDERS_H_

static inline void static_collide(entity_t *self, entity_t *moving)
{
    if (moving->pos.v1.x + moving->speed + 0.01f > self->pos.v2.x) {
        moving->pos.v1.x = self->pos.v2.x;
        moving->pos.v2.x = moving->pos.v1.x + moving->size[0];
    } else if (self->pos.v1.x + moving->speed + 0.01f > moving->pos.v2.x) {
        moving->pos.v2.x = self->pos.v1.x;
        moving->pos.v1.x = moving->pos.v2.x - moving->size[0];
    }
    if (moving->pos.v1.y + moving->speed + 0.01f > self->pos.v2.y) {
        moving->pos.v1.y = self->pos.v2.y;
        moving->pos.v2.y = moving->pos.v1.y + moving->size[1];
    } else if (self->pos.v1.y + moving->speed + 0.01f > moving->pos.v2.y) {
        moving->pos.v2.y = self->pos.v1.y;
        moving->pos.v1.y = moving->pos.v2.y - moving->size[1];
    }
}

static inline void dynamic_collide_force(entity_t *self, entity_t *mov)
{
    if (mov->pos.v1.x + mov->speed + self->speed + 0.01f > self->pos.v2.x) {
        mov->pos.v1.x = self->pos.v2.x;
        mov->pos.v2.x = mov->pos.v1.x + mov->size[0];
    } else if (self->pos.v1.x + mov->speed + self->speed + 0.01f >
        mov->pos.v2.x) {
        mov->pos.v2.x = self->pos.v1.x;
        mov->pos.v1.x = mov->pos.v2.x - mov->size[0];
    }
    if (mov->pos.v1.y + mov->speed + self->speed + 0.01f > self->pos.v2.y) {
        mov->pos.v1.y = self->pos.v2.y;
        mov->pos.v2.y = mov->pos.v1.y + mov->size[1];
    } else if (self->pos.v1.y + mov->speed + self->speed + 0.01f >
        mov->pos.v2.y) {
        mov->pos.v2.y = self->pos.v1.y;
        mov->pos.v1.y = mov->pos.v2.y - mov->size[1];
    }
}

#endif /* BASIC_COLLIDERS_H_ */
