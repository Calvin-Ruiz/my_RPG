/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** npc_event_io.c
*/

#include <entity.h>
#include <data_storage.h>
#include <solid_event.h>
#include <dynamic_npc.h>

event_t *load_solid_event(event_t *self, int fd)
{
    event_t *new = malloc(sizeof(*self));
    event_save_t save;

    read(fd, (char *) &save, sizeof(save));
    *new = *self;
    new->pos.v1 = save.pos;
    new->pos.v2 = (sfVector2f) {save.pos.x + new->size[0],
        save.pos.y + new->size[1]};
    new->sprite += save.frame_dec;
    new->frame_dec = save.frame_dec;
    new->frame = save.frame;
    new->tag_id = save.tag_id;
    if (save.tag_id != (ushort_t) -1)
        new->tag = *get_tag_from_id(get_data_storage()->saved, save.tag_id);
    return (new);
}

void save_solid_event(event_t *self, int fd)
{
    event_save_t event_save = {self->pos.v1, self->frame_dec, self->frame,
        self->tag_id};

    write(fd, (char *) &event_save, sizeof(event_save));
}

static way_t *rebuild_way(uchar_t nb_ways, int fd)
{
    const char saved_way_size = sizeof(way_t) - sizeof(void *);
    way_t *way = my_malloc(nb_ways * sizeof(way_t));
    way_t *first = way;

    while (nb_ways--) {
        way->next = way + 1;
        read(fd, ((char *) way++) + sizeof(void *), saved_way_size);
    }
    way[-1].next = first;
    return (first);
}

npc_t *load_dynamic_npc(npc_t *self, int fd)
{
    npc_t *new = malloc(sizeof(*self));
    npc_save_t save;

    read(fd, (char *) &save, sizeof(save));
    *new = *self;
    new->pos.v1 = save.pos;
    new->pos.v2 = (sfVector2f) {save.pos.x + new->size[0],
        save.pos.y + new->size[1]};
    new->sprite += save.frame_dec;
    new->frame_dec = save.frame_dec;
    new->frame = save.frame;
    new->tag_id = save.tag_id;
    if (save.tag_id != (ushort_t) -1)
        new->tag = *get_tag_from_id(get_data_storage()->saved, save.tag_id);
    new->speed = save.speed;
    new->wait_time = save.wait_time;
    new->way = rebuild_way(save.nb_ways, fd);
    return (new);
}

void save_dynamic_npc(npc_t *self, int fd)
{
    way_t *tmp = self->way->next;
    const char sizeof_way = sizeof(way_t) - sizeof(void *);
    npc_save_t npc_save = {self->pos.v1, self->frame_dec, self->frame,
        self->tag_id, self->speed, self->wait_time, 1};

    while (tmp != self->way) {
        npc_save.nb_ways++;
        tmp = tmp->next;
    }
    write(fd, (char *) &npc_save, sizeof(npc_save));
    tmp = self->way;
    while (npc_save.nb_ways--) {
        write(fd, ((char *) tmp) + sizeof(void *), sizeof_way);
        tmp = tmp->next;
    }
}
