/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** entitylist.h
*/

#ifndef ENTITYLIST_H_
#define ENTITYLIST_H_

#include <dict.h>
#include <entity_display.h>

void entitylist_update(entitylist_t *self, void *datas);
entitylist_t *create_entitylist(void);
void destroy_entitylist(entitylist_t *entitylist);

static inline entity_t *get_entity_by_id(dict_t *dict, int pos)
{
    while (pos-- && dict)
        dict = dict->next;
    return (dict->data);
}

static inline entity_t *get_colliding(entity_t *self, entitylist_t *elist)
{
    static entity_t *tmp = NULL;

    if (tmp == NULL)
        tmp = (entity_t *) elist;
    while (tmp->next) {
        tmp = tmp->next;
        if (self->pos.v1.x < tmp->pos.v2.x && self->pos.v2.x > tmp->pos.v1.x &&
            self->pos.v1.y < tmp->pos.v2.y && self->pos.v2.y > tmp->pos.v1.y)
            return (tmp);
    }
    return (NULL);
}

static inline entity_t **get_colliding_pair(entitylist_t *self,
    entitylist_t *with)
{
    static entity_t *tmp[2] = {NULL, NULL};

    if (tmp[0] == NULL)
        tmp[0] = self->next;
    while (tmp[0]) {
        tmp[1] = get_colliding(tmp[0], with);
        if (tmp[1])
            return (tmp);
        tmp[0] = tmp[0]->next;
    }
    return (NULL);
}

static inline void append_to_entitylist(entitylist_t *display_list,
    entitylist_t *self, entity_t *entity)
{
    if (entity == NULL)
        return;
    conditionnal_insertion(&display_list->next, entity);
    entity->next = self->next;
    if (self->next)
        self->next->prev = entity;
    self->next = entity;
}

#endif /* ENTITYLIST_H_ */
