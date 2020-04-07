/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** entitylist.c
*/
#include <entity.h>
#include <data_storage.h>

void entitylist_update(entitylist_t *self, data_storage_t *datas)
{
    entity_t **entity = &(self->next);
    entity_t *tmp;
    sfTime time = sfClock_getElapsedTime(self->clock);
    long long delta_time = time.microseconds - self->last;

    self->last = time.microseconds;
    while (*entity) {
        if ((*entity)->health <= 0) {
            tmp = (*entity)->next;
            (*entity)->destroy(*entity);
            *entity = tmp;
        } else {
            (*entity)->update(*entity, datas->entitylists,
                delta_time);
            entity = &((*entity)->next);
        }
    }
}

entitylist_t *create_entitylist(void)
{
    entitylist_t *new = malloc(sizeof(entitylist_t));

    new->next = NULL;
    new->last = 0;
    new->clock = sfClock_create();
    new->update = entitylist_update;
    return (new);
}

void destroy_entitylist(entitylist_t *entitylist)
{
    entity_t *tmp;
    entity_t *tmp2;

    if (entitylist == NULL)
        return;
    tmp = entitylist->next;
    while (tmp) {
        tmp2 = tmp->next;
        tmp->destroy(tmp);
        tmp = tmp2;
    }
    sfClock_destroy(entitylist->clock);
    free(entitylist);
}
