/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** dynamic_npc.c
*/

#include <entity.h>
#include <data_storage.h>
#include <dynamic_npc.h>

void create_way_cmd(char **arr)
{
    int nb_ways = ((long) arr[-1] - 2) / 3;
    way_t *tmp = my_malloc(sizeof(way_t) * nb_ways);
    way_t *first = tmp;

    *(way_t **) arr[1] = tmp;
    arr += 2;
    while (nb_ways--) {
        *tmp = (way_t) {tmp + 1, (sfVector2f) {(long) arr[0], (long) arr[1]},
            (long) arr[2]};
        tmp++;
        arr += 3;
    }
    tmp[-1].next = first;
}

void create_npc_cmd(char **arr)
{
    npc_t *npc = malloc(sizeof(npc_t));
    data_storage_t *datas = get_data_storage();
    char *name = arr[1];

    arr = create_entity_base((entity_t *) npc, &datas->entities, arr);
    if (arr == NULL) {
        my_puterr("\e[91mFatal : Failed to build '");
        my_puterr(name);
        my_puterr("' npc.\n\e[0m");
        return;
    }
    npc->event = (void (*)(npc_t *self, player_t *player)) arr[0];
    npc->command_name = my_tmpdup(arr[1]);
    npc->tag_id = -1;
    npc->tag = NULL;
}

npc_t *new_npc(char **arr)
{
    npc_t *npc = malloc(sizeof(npc_t));

    if (*arr == NULL)
        return (NULL);
    if (arr[1] == NULL) {
        my_puterr("\e[94mNewNpcError : nullptr received for way\n\e[0m");
        return (NULL);
    }
    *npc = *(npc_t *) *arr;
    npc->way = *(way_t **) arr[1];
    npc->wait_time = npc->way->wait_time;
    npc->pos.v1 = npc->way->pos;
    npc->pos.v2 = (sfVector2f) {npc->pos.v1.x + npc->size[0],
        npc->pos.v1.y + npc->size[1]};
    npc->tag_id = -1;
    return (npc);
}

void default_npc_update(npc_t *self, int delta_time)
{
    self->timer += delta_time;
    if (self->timer >= self->frame_delay) {
        self->timer -= self->frame_delay;
        self->frame = (self->frame + 1) % self->size[2];
    }
    self->sprite -= self->frame_dec;
    move_npc(self);
    self->sprite += self->frame_dec;
    self->pos.v2.x = self->pos.v1.x + *self->size;
    self->pos.v2.y = self->pos.v1.y + self->size[1];
    if (self->pos.v1.x != self->way->pos.x
        || self->pos.v1.y != self->way->pos.y || self->wait_time-- > 0)
        return;
    self->way = self->way->next;
    self->wait_time = self->way->wait_time;
}

void destroy_npc(npc_t *self)
{
    free(self);
}
