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
    entity_t *tmp = (*entity)->disp_next;

    while (tmp) {
        if ((*entity)->health <= 0) {
            destroy_this_entity(*entity);
            *entity = tmp;
            tmp = tmp->disp_next;
            continue;
        }
        draw_this_entity(*entity, window);
        if ((*entity)->speed > 0.f)
            *entity = (*entity)->disp_next;
        else
            entity = &(*entity)->disp_next;
        tmp = (*entity)->disp_next;
    }
    last_display_entities(window, entity);
}
