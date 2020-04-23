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

#endif /* EXT_STRUCT_1_H_ */
