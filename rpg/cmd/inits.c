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
#include <item_list.h>
#include <trading.h>
#include <quest.h>
#include <quest_list.h>

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
    append_to_dict(cmd, "give_capacity", give_capacity_cmd);
    append_to_dict(cmd, "check_quest", check_quest);
    append_to_dict(cmd, "create_quest", create_quest_cmd);
}

static dict_t *get_internal_func_part_2(void)
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

static dict_t *get_internal_func_part(void)
{
    dict_t *new = get_internal_func_part_2();

    append_to_dict(&new, "enemy_atk_sprite", enemy_atk_sprite);
    append_to_dict(&new, "use_capacity", use_capacity);
    append_to_dict(&new, "dtext_update_int", update_dynamic_text_from_int);
    append_to_dict(&new, "dtext_update_2int", update_dynamic_text_from_2int);
    append_to_dict(&new, "exit_menu", exit_menu);
    append_to_dict(&new, "update_capacity_selection",
        update_capacity_selection);
    append_to_dict(&new, "action_list_clic", action_list_clic);
    append_to_dict(&new, "on_clic_item_list", on_clic_item_list);
    append_to_dict(&new, "update_item_list", update_item_list);
    append_to_dict(&new, "close_menu", close_menu);
    append_to_dict(&new, "trade", trade_event);
    append_to_dict(&new, "on_clic_trade_list", on_clic_trade_list);
    append_to_dict(&new, "update_trade_list", update_trade_list);
    append_to_dict(&new, "destroy_player", destroy_player);
    append_to_dict(&new, "destroy_item_list", destroy_item_list_content);
    append_to_dict(&new, "destroy_trade_list", destroy_trade_list_content);
    return (new);
}

dict_t *get_internal_func(void)
{
    dict_t *new = get_internal_func_part();

    append_to_dict(&new, "recover_effect", recover_effect);
    append_to_dict(&new, "equip_weapon", equip_item);
    append_to_dict(&new, "on_clic_fight_item", on_clic_fight_item);
    append_to_dict(&new, "open_inventory", open_inventory);
    append_to_dict(&new, "use_item_for_me", use_item_for_me);
    append_to_dict(&new, "use_item_for_you", use_item_for_you);
    append_to_dict(&new, "choice_yes", choice_yes);
    append_to_dict(&new, "choice_no", choice_no);
    append_to_dict(&new, "update_quest_list", update_quest_list);
    append_to_dict(&new, "destroy_quest_list", destroy_quest_list_content);
    append_to_dict(&new, "open_quest_menu", open_quest_menu);
    return (new);
}
