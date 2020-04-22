/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** npc.c
*/

#include <entitybase.h>
#include <entitylist.h>
#include <data_storage.h>
#include <player.h>
#include <npc.h>

void npc_update(entitylist_t *self, player_t *ent)
{
    entity_t *tmp = self->next;
    long long time = sfClock_getElapsedTime(self->clock).microseconds;
    int delta_time = time - self->last;
    data_storage_t *datas = get_data_storage();

    self->last = time;
    while (tmp) {
        tmp->update(tmp, delta_time);
        if (ent->pos.v1.x < tmp->pos.v2.x && ent->pos.v2.x > tmp->pos.v1.x &&
            ent->pos.v1.y < tmp->pos.v2.y && ent->pos.v2.y > tmp->pos.v1.y) {
            npc_collision((npc_t *) tmp, ent);
        }
        if (tmp->speed > 0.f)
            conditionnal_insertion(&datas->entitylists[0]->next, tmp);
        tmp = tmp->next;
    }
}
