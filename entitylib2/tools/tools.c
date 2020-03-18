/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** tools.c
*/
#include <fcntl.h>
#include <entitybase.h>
#include <data_storage.h>
#include <fast_get_next_line.h>
#include <tools.h>

void apply_all(entitylist_t *self, void (*action)(), void *args)
{
    entity_t *entity = self->next;

    while (entity) {
        action(entity, args);
        entity = entity->next;
    }
}

uint_t *get_size(uint_t width, uint_t height, uint_t nbr_rows)
{
    uint_t *size = malloc(sizeof(uint_t) * 3);

    if (size == NULL)
        return (NULL);
    size[0] = width;
    size[1] = height;
    size[2] = nbr_rows;
    return (size);
}

void no_update(void *ptr)
{
    (void) ptr;
}

void my_putnbr(int nb)
{
    if (nb > 9)
        my_putnbr(nb / 10);
    my_putchar('0' + nb % 10);
}
