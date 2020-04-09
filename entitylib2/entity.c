/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** entity.c
*/
#include <entity.h>
#include <data_storage.h>
#include <etools.h>
#include <dict.h>

void default_destroy(void *self)
{
    free(self);
}

void entity_blit(entity_t *self, sfRenderWindow *window)
{
    sfSprite_setPosition(self->sprite[self->frame], self->pos.v1);
    sfRenderWindow_drawSprite(window, self->sprite[self->frame], NULL);
}

char **create_entity_base(entity_t *new, dict_t **entities, char **arr)
{
    if ((long) arr[-1] < 14 || new == NULL)
        return (NULL);
    *new = (entity_t) {0, 0, 0, *entities ? ((entity_t *) (*entities)->data)->id
        + 1 : 0, malloc(sizeof(void *) * (long) arr[5] * (long) arr[6]),
        get_size((long *) arr + 3), (long) arr[7], 0, (long) arr[8] * 10000, 0, 0, (pos_t) {(sfVector2f) {0, 0}, (sfVector2f) {0, 0}},
        (void (*)()) arr[9], (void *(*)()) arr[10], (void (*)()) arr[11],
        (void *(*)()) arr[12], (void (*)()) arr[13]};
    if (create_sprite(new->sprite, (sfTexture *) arr[2], new->size))
        return (NULL);
    append_to_dict(entities, arr[1], new);
    return (arr + 14);
}

char create_sprite(sfSprite **sprite, sfTexture *texture, ushort_t *size)
{
    unsigned int i = -1;
    int j;
    sfIntRect rect = {0, 0, size[0], size[1]};

    if (sprite == NULL || size == NULL)
        return (1);
    while (++i < size[2]) {
        j = -1;
        rect.left = 0;
        while (++j < 4) {
            *sprite = sfSprite_create();
            sfSprite_setTexture(*sprite, texture, sfFalse);
            sfSprite_setTextureRect(*(sprite++), rect);
            rect.left += size[0];
        }
        rect.top += size[1];
    }
    return (0);
}

void free_entity(entity_t *entity)
{
    if (entity == NULL)
        return;
    int i = -1;
    const int end = entity->size[2] * entity->size[3];

    while (++i < end)
        sfSprite_destroy(entity->sprite[i]);
    free(entity->sprite);
    free(entity->size);
    free(entity);
}
