/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** structs.c
*/
#include <dict.h>
#include <entitybase.h>
#include <player.h>
#include <data_storage.h>
#include <npc.h>
#include <structs_1.h>
#include <ext_struct_1.h>

void define_external_structs(dict_t **structs)
{
    append_to_dict(structs, "npc", define_npc_structure(NULL));
    append_to_dict(structs, "player", define_player_structure(NULL));
}
