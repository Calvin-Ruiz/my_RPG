/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** etools.c
*/
#include <fcntl.h>
#include <entitybase.h>
#include <data_storage.h>
#include <fast_get_next_line.h>
#include <etools.h>

void apply_all(entitylist_t *self, void (*action)(), void *args)
{
    entity_t *entity = self->next;

    while (entity) {
        action(entity, args);
        entity = entity->next;
    }
}

ushort_t *get_size(ushort_t width, ushort_t height, ushort_t nb_frames,
    ushort_t nb_directions)
{
    ushort_t *size = malloc(sizeof(uint_t) * 3);

    if (size == NULL)
        return (NULL);
    size[0] = width;
    size[1] = height;
    size[2] = nb_frames;
    size[2] = nb_directions;
    return (size);
}

void no_update(void *ptr)
{
    (void) ptr;
}
