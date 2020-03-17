/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** entity.h
*/

#ifndef ENTITY_H_
#define ENTITY_H_

#include "entitybase.h"

void no_update(void *ptr);
void entity_blit(entity_t *self, sfRenderWindow *window);
void create_entity_base(entity_t *new, uint_t *size, float fdelay, int hp);
char create_sprite(sfSprite **sprite, sfTexture *texture, uint_t *size);
void free_entity(entity_t *entity);

#endif /* ENTITY_H_ */
