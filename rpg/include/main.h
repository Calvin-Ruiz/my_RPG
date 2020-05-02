/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** main.h
*/

#ifndef MAIN_H_
#define MAIN_H_

#include <entitylib.h>
#include <player_func.h>
#include <tools.h>

enum {
    DISPLAY_LIST,
    NPC_LIST,
    EVENT_LIST,
    DECOR_LIST,
    NB_ENTITYLIST,
};

void init_some_datas(data_storage_t *datas);
void mainloop(data_storage_t *datas, sfRenderWindow *window);
void open_inventory(data_storage_t *datas);
int main(void);

static inline int my_full_reset(void)
{
    my_malloc(-1);
    return (main());
}

#endif /* MAIN_H_ */
