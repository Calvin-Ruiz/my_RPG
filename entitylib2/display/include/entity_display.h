/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** entity_display.h
*/

#ifndef ENTITY_DISPLAY_H_
#define ENTITY_DISPLAY_H_

void display_entities(sfRenderWindow *window, entity_t **entity);

static inline void conditionnal_insertion(entity_t **entity, entity_t *tmp)
{
    while (*entity && ((*entity)->pos.v1.x >= tmp->pos.v2.x ||
        (*entity)->pos.v2.y <= tmp->pos.v1.y)) {
        entity = &(*entity)->disp_next;
    }
    tmp->disp_next = *entity;
    *entity = tmp;
}

static inline void conditionnal_permutation(entity_t **entity, entity_t *tmp)
{
    if ((*entity)->pos.v1.x < tmp->pos.v2.x &&
        (*entity)->pos.v2.y > tmp->pos.v1.y) {
        (*entity)->disp_next = tmp->disp_next;
        tmp->disp_next = *entity;
        *entity = tmp;
    }
}

static inline void draw_this_entity(entity_t *self, sfRenderWindow *window)
{
    sfSprite_setPosition(self->sprite[self->frame], self->pos.v1);
    sfRenderWindow_drawSprite(window, self->sprite[self->frame], NULL);
}

static inline void destroy_this_entity(entity_t *entity)
{
    if (entity->next) {
        entity->next->prev = entity->prev;
        entity->prev->next = entity->next;
    } else
        entity->prev->next = NULL;
    entity->destroy(entity);
}

static inline void last_display_entities(sfRenderWindow *window,
    entity_t **entity) {
    if ((*entity)->health <= 0) {
        destroy_this_entity(*entity);
        *entity = NULL;
        return;
    }
    draw_this_entity(*entity, window);
    if ((*entity)->speed > 0.f)
        *entity = NULL;
}

#endif /* ENTITY_DISPLAY_H_ */
