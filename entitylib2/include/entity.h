/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** entity.h
*/

#ifndef ENTITY_H_
#define ENTITY_H_

#include <entitybase.h>
#include <dict.h>

void no_update(void *ptr);
void entity_blit(entity_t *self, sfRenderWindow *window);
char **create_entity_base(entity_t *new, dict_t **entities, char **arr);
char create_sprite(sfSprite **sprite, sfTexture *texture, ushort_t *size);
void free_entity(entity_t *entity);

#endif /* ENTITY_H_ */
