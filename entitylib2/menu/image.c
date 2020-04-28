/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** image.c
*/

#include <entitybase.h>
#include <data_storage.h>
#include <menu.h>

image_t *create_image(sfTexture *texture, pos_t *pos)
{
    image_t *new = malloc(sizeof(image_t));
    sfVector2u size = sfTexture_getSize(texture);

    new->image = sfSprite_create();
    if (new->image == NULL)
        return (NULL);
    sfSprite_setTexture(new->image, texture, sfTrue);
    sfSprite_setPosition(new->image, pos->v1);
    sfSprite_setScale(new->image, (sfVector2f) {pos->v2.x / (float) size.x,
        pos->v2.y / (float) size.y});
    return (new);
}

void update_image_array(sfRenderWindow *window, image_t *image)
{
    while (image) {
        sfRenderWindow_drawSprite(window, image->image, NULL);
        image = image->next;
    }
}
