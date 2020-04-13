/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** event.c
*/

#include <entitybase.h>
#include <entitylist.h>
#include <player.h>
#include <event.h>
#include <basic_colliders.h>

void event_update(entitylist_t *self, player_t *ent)
{
    event_t *tmp = (event_t *) self->next;
    long long time = sfClock_getElapsedTime(self->clock).microseconds;
    int delta_time = time - self->last;

    while (tmp) {
        tmp->update(tmp, delta_time);
        if (ent->pos.v1.x < tmp->pos.v2.x && ent->pos.v2.x > tmp->pos.v1.x &&
            ent->pos.v1.y < tmp->pos.v2.y && ent->pos.v2.y > tmp->pos.v1.y) {
            static_collide((entity_t *) tmp, (entity_t *) ent);
            tmp->event(tmp, ent);
        }
        tmp = tmp->next;
    }
}
