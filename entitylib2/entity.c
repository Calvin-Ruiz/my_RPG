/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** entity.c
*/
#include <entity.h>
#include <tools.h>
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

void create_entity_base(entity_t *new, float fdelay, int hp, dict_t *entities)
{
    new->health = hp;
    new->max_health = hp;
    new->timer = 0;
    new->frame_delay = fdelay * 1000000;
    new->frame_dec = 0;
    new->frame = 0;
    new->destroy = default_destroy;
    new->load = NULL;
    new->save = NULL;
    new->id = entities ? ((entity_t *) entities->data)->id + 1 : 0;
}

char create_sprite(sfSprite **sprite, sfTexture *texture, ushort_t *size)
{
    unsigned int i = -1;
    int j;
    sfIntRect rect = {0, 0, size[0], size[1]};

    if (sprite == NULL)
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
