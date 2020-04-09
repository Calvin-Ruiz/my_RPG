/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** cmds.h
*/

#include <entitylib.h>
#include <player.h>
#include <solid_decor.h>
#include <cmds.h>
#include <etools.h>

void init_external_cmds(dict_t **cmd)
{
    append_to_dict(cmd, "create_player", create_player_cmd);
    append_to_dict(cmd, "create_decor", create_solid_decor_cmd);
}

dict_t *get_internal_func(void)
{
    dict_t *new = NULL;

    append_to_dict(&new, "def_destroy", default_destroy);
    append_to_dict(&new, "pupdate", update_player);
    append_to_dict(&new, "new_decor", new_solid_decor);
    return (new);
}
