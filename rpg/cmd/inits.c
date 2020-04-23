/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** cmds.c
*/

#include <entitylib.h>
#include <player.h>
#include <solid_decor.h>
#include <solid_event.h>
#include <dynamic_npc.h>
#include <cmds.h>
#include <etools.h>

dict_t *get_sf_colors(void)
{
    dict_t *tmp = NULL;

    append_to_dict(&tmp, "black", *(void **) &sfBlack);
    append_to_dict(&tmp, "white", *(void **) &sfWhite);
    append_to_dict(&tmp, "red", *(void **) &sfRed);
    append_to_dict(&tmp, "green", *(void **) &sfGreen);
    append_to_dict(&tmp, "blue", *(void **) &sfBlue);
    append_to_dict(&tmp, "yellow", *(void **) &sfYellow);
    append_to_dict(&tmp, "magenta", *(void **) &sfMagenta);
    append_to_dict(&tmp, "cyan", *(void **) &sfCyan);
    append_to_dict(&tmp, "transparent", *(void **) &sfTransparent);
    return (tmp);
}

void init_external_cmds(dict_t **cmd)
{
    append_to_dict(cmd, "create_item", create_item_cmd);
    append_to_dict(cmd, "create_player", create_player_cmd);
    append_to_dict(cmd, "create_decor", create_solid_decor_cmd);
    append_to_dict(cmd, "create_event", create_event_cmd);
    append_to_dict(cmd, "create_npc", create_npc_cmd);
    append_to_dict(cmd, "create_way", create_way_cmd);
    append_to_dict(cmd, "give_item", give_item_cmd);
}

dict_t *get_internal_func(void)
{
    dict_t *new = NULL;

    append_to_dict(&new, "def_destroy", default_destroy);
    append_to_dict(&new, "pupdate", update_player);
    append_to_dict(&new, "new_decor", new_solid_decor);
    append_to_dict(&new, "deco_load", load_solid_decor);
    append_to_dict(&new, "deco_save", save_solid_decor);
    append_to_dict(&new, "npc_update", default_npc_update);
    append_to_dict(&new, "destroy_npc", destroy_npc);
    append_to_dict(&new, "new_npc", new_npc);
    append_to_dict(&new, "event_update", default_event_update);
    append_to_dict(&new, "destroy_event", destroy_event);
    append_to_dict(&new, "new_event", new_solid_event);
    return (new);
}
