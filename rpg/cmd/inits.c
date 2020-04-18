/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** cmds.c
*/

#include <entitylib.h>
#include <player.h>
#include <solid_decor.h>
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
}

dict_t *get_internal_func(void)
{
    dict_t *new = NULL;

    append_to_dict(&new, "def_destroy", default_destroy);
    append_to_dict(&new, "pupdate", update_player);
    append_to_dict(&new, "new_decor", new_solid_decor);
    return (new);
}
