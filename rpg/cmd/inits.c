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
#include <system_cmd.h>
#include <enemy.h>
#include <fight.h>
#include <action_list.h>

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

static void init_external_cmds_part(dict_t **cmd)
{
    append_to_dict(cmd, "create_item", create_item_cmd);
    append_to_dict(cmd, "create_player", create_player_cmd);
    append_to_dict(cmd, "create_decor", create_solid_decor_cmd);
    append_to_dict(cmd, "create_event", create_event_cmd);
    append_to_dict(cmd, "create_npc", create_npc_cmd);
    append_to_dict(cmd, "create_way", create_way_cmd);
    append_to_dict(cmd, "give_item", give_item_cmd);
    append_to_dict(cmd, "op", better_operator);
    append_to_dict(cmd, "fop", float_operator);
    append_to_dict(cmd, "set_from_var", set_from_var);
    append_to_dict(cmd, "read", read_cmd);
    append_to_dict(cmd, "write", write_cmd);
    append_to_dict(cmd, "putstr", putstr_cmd);
    append_to_dict(cmd, "open", open_cmd);
    append_to_dict(cmd, "close", close_cmd);
    append_to_dict(cmd, "randint", randint_cmd);
    append_to_dict(cmd, "set_tag", set_tag_cmd);
    append_to_dict(cmd, "create_sprite_anim", create_sprite_anim);
    append_to_dict(cmd, "create_capacity", create_capacity);
    append_to_dict(cmd, "create_enemy", create_enemy_cmd);
}

void init_external_cmds(dict_t **cmd)
{
    init_external_cmds_part(cmd);
    append_to_dict(cmd, "said", my_said);
    append_to_dict(cmd, "create_dynamic_list", create_dynamic_list_cmd);
}

static dict_t *get_internal_func_part(void)
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
    append_to_dict(&new, "npc_load", load_dynamic_npc);
    append_to_dict(&new, "npc_save", save_dynamic_npc);
    append_to_dict(&new, "event_load", load_solid_event);
    append_to_dict(&new, "event_save", save_solid_event);
    append_to_dict(&new, "fight", engage_fight_event);
    append_to_dict(&new, "player_atk_sprite", player_atk_sprite);
    return (new);
}

dict_t *get_internal_func(void)
{
    dict_t *new = get_internal_func_part();

    append_to_dict(&new, "enemy_atk_sprite", enemy_atk_sprite);
    append_to_dict(&new, "use_capacity", use_capacity);
    append_to_dict(&new, "dtext_update_int", update_dynamic_text_from_int);
    append_to_dict(&new, "dtext_update_2int", update_dynamic_text_from_2int);
    append_to_dict(&new, "exit_menu", exit_menu);
    append_to_dict(&new, "update_capacity_selection",
        update_capacity_selection);
    append_to_dict(&new, "action_list_clic", action_list_clic);
    return (new);
}
