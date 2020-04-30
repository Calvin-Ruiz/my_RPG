/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** player_io.h
*/

#ifndef PLAYER_IO_H_
#define PLAYER_IO_H_

void save_player(player_t *self, data_storage_t *datas);
void load_player(player_t *self, data_storage_t *datas);

static inline capacity_t *get_capacity_from_id(dict_t *capacities, short id)
{
    while (capacities) {
        if (((capacity_t *) capacities->data)->id == id)
            return (capacities->data);
        capacities = capacities->next;
    }
    return (NULL);
}

static inline item_t *get_item_from_id(item_t *items, short id)
{
    while (items) {
        if (items->id == id)
            return (items);
        items = items->next;
    }
    return (NULL);
}

#endif /* PLAYER_IO_H_ */
