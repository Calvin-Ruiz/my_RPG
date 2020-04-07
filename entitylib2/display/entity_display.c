/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** entity_display.c
*/
#include <entitybase.h>
#include <data_storage.h>
#include <entity_display.h>

void display_entities(sfRenderWindow *window, entity_t **entity)
{
    entity_t *tmp = (*entity)->next;

    while (tmp) {
        if ((*entity)->health <= 0) {
            destroy_this_entity(*entity);
            *entity = tmp;
            tmp = tmp->next;
            continue;
        }
        conditionnal_permutation(entity, tmp);
        draw_this_entity(*entity, window);
        entity = &(*entity)->next;
        tmp = (*entity)->next;
    }
    if ((*entity)->health <= 0) {
        destroy_this_entity(*entity);
        *entity = NULL;
        return;
    }
    draw_this_entity(*entity, window);
}
