/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** item_action.c
*/

#include <entitybase.h>
#include <data_storage.h>
#include <player.h>

void recover_effect(item_t *item, player_t *player)
{
    player->hp += *(int *) item->data;
    if (player->hp > player->max_hp)
        player->hp = player->max_hp;
}

void equip_item(item_t *item, player_t *player)
{
    u_char type = ((char *) item->data)[7];

    player->equip[type] = *(equip_t *) item->data;
    calculate_final_characteristics(player);
}
