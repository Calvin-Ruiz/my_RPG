/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** player.c
*/

#include <entity.h>
#include <data_storage.h>
#include <tools.h>
#include <player.h>

void create_player_cmd(char **arr)
{
    player_t *player = malloc(sizeof(player_t));
    data_storage_t *datas = get_data_storage();

    arr = create_entity_base((entity_t *) player, &datas->entities, arr);
    if (arr == NULL) {
        my_puterr("\e[91mFatal : Faild to create player\n\e[0m");
        return;
    }
    datas->player = player;
    player->disp_next = datas->entitylists[0]->next;
    datas->entitylists[0]->next = (entity_t *) player;
}
