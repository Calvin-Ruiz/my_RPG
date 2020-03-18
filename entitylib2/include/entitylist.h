/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** entitylist.h
*/

#ifndef ENTITYLIST_H_
#define ENTITYLIST_H_

void entitylist_update(entitylist_t *self, void *datas);
entitylist_t *create_entitylist(void);
void destroy_entitylist(entitylist_t *entitylist);

#endif /* ENTITYLIST_H_ */
