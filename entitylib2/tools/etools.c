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

ushort_t *get_size(long *arr)
{
    ushort_t *size = malloc(sizeof(uint_t) * 4);

    if (size == NULL)
        return (NULL);
    size[0] = arr[0];
    size[1] = arr[1];
    size[2] = arr[2];
    size[3] = arr[3];
    return (size);
}

void no_update(void *ptr)
{
    (void) ptr;
}
