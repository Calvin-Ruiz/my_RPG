/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** action_list.h
*/

#ifndef ACTION_LIST_H_
#define ACTION_LIST_H_

void use_capacity(void *data);
void update_capacity_selection(dynamic_list_t *self, sfRenderWindow *window,
    data_storage_t *datas, sfVector2f *mouse);
char action_list_clic(dynamic_list_t *self, sfVector2f *pos);

#endif /* ACTION_LIST_H_ */
