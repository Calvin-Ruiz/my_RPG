/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** ext_struct_1.h
*/

#ifndef EXT_STRUCT_1_H_
#define EXT_STRUCT_1_H_

static inline dict_t *define_npc_structure(npc_t * const ref)
{
    dict_t *new = define_entity(NULL);

    append_to_dict(&new, "event", &ref->event);
    append_to_dict(&new, "command_name", &ref->command_name);
    append_to_dict(&new, "tag_id", &ref->tag_id);
    append_to_dict(&new, "tag", &ref->tag);
    append_to_dict(&new, "way", &ref->way);
    append_to_dict(&new, "wait_time", &ref->wait_time);
    return (new);
}

static inline dict_t *define_player_structure(player_t * const ref)
{
    dict_t *new = define_entity(NULL);

    append_to_dict(&new, "inventory", &ref->inventory);
    append_to_dict(&new, "capacity", &ref->capacity);
    append_to_dict(&new, "hp", &ref->hp);
    append_to_dict(&new, "max_hp", &ref->max_hp);
    append_to_dict(&new, "atk", &ref->atk);
    append_to_dict(&new, "def", &ref->def);
    append_to_dict(&new, "money", &ref->money);
    append_to_dict(&new, "xp", &ref->xp);
    append_to_dict(&new, "level", &ref->level);
    return (new);
}

#endif /* EXT_STRUCT_1_H_ */
