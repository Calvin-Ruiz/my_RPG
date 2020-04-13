/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** npc.c
*/

#include <entitybase.h>
#include <entitylist.h>
#include <player.h>
#include <npc.h>

void npc_update(entitylist_t *self, player_t *ent)
{
    entity_t *tmp = self->next;

    while (tmp) {
        // update
        if (ent->pos.v1.x < tmp->pos.v2.x && ent->pos.v2.x > tmp->pos.v1.x &&
            ent->pos.v1.y < tmp->pos.v2.y && ent->pos.v2.y > tmp->pos.v1.y) {
            npc_collision(tmp, ent);
        }
        tmp = tmp->next;
    }
}
