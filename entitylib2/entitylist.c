/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** entitylist.c
*/
#include <entity.h>
#include <data_storage.h>

void entitylist_pre_draw(entitylist_t *self, sfRenderWindow *window)
{
    entity_t *entity = self->next;

    while (entity) {
        entity->pre_draw(entity, window);
        entity = entity->next;
    }
}

char entitylist_update(entitylist_t *self, data_storage_t *datas)
{
    entity_t **entity = &(self->next);
    entity_t *tmp;
    sfTime time = sfClock_getElapsedTime(self->clock);
    long long delta_time = time.microseconds - self->last;
    uchar_t killed_count = 0;

    self->last = time.microseconds;
    while (*entity) {
        if ((*entity)->health <= 0) {
            tmp = (*entity)->next;
            (*entity)->destroy(*entity);
            *entity = tmp;
            killed_count++;
        } else {
            (*entity)->update(*entity, datas->entitylists,
                delta_time, datas->window);
            entity = &((*entity)->next);
        }
    }
    return (killed_count);
}

entitylist_t *create_entitylist(void)
{
    entitylist_t *new = malloc(sizeof(entitylist_t));

    new->next = NULL;
    new->last = 0;
    new->clock = sfClock_create();
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
