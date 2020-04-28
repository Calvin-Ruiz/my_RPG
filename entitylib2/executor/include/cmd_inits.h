/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** cmd_inits.h
*/

#ifndef CMD_INITS_H_
#define CMD_INITS_H_

#include <enemy.h>

static inline void reference_sizeof(dict_t **var)
{
    dict_t *dict = NULL;

    append_to_dict(&dict, "sfVector2f", (void *) sizeof(sfVector2f));
    append_to_dict(&dict, "dict_t", (void *) sizeof(dict_t));
    append_to_dict(&dict, "entity_t", (void *) sizeof(entity_t));
    append_to_dict(&dict, "entitylist_t", (void *) sizeof(entitylist_t));
    append_to_dict(&dict, "menu_t", (void *) sizeof(menu_t));
    append_to_dict(&dict, "ptr", (void *) sizeof(void *));
    append_to_dict(&dict, "char", (void *) sizeof(char));
    append_to_dict(&dict, "double", (void *) sizeof(double));
    append_to_dict(&dict, "float", (void *) sizeof(float));
    append_to_dict(&dict, "short", (void *) sizeof(short));
    append_to_dict(&dict, "long", (void *) sizeof(long));
    append_to_dict(&dict, "int", (void *) sizeof(int));
    append_to_dict(&dict, "particle_param", (void *) sizeof(particle_param_t));
    append_to_dict(&dict, "particle_attr_t", (void *) sizeof(particle_attr_t));
    append_to_dict(&dict, "enemy_t", (void *) sizeof(enemy_t));
    append_to_dict(var, "sizeof", dict);
}

static inline void sub_init_vars(dict_t **var, data_storage_t *datas)
{
    append_to_dict(var, "texture", datas->textures);
    append_to_dict(var, "thread", NULL);
    append_to_dict(var, "sys", NULL);
    append_to_dict(var, "datas", datas);
    append_to_dict(var, "struct", define_structs());
    reference_sizeof(var);
    append_to_dict(var, "sbuff", datas->sound_buffs);
    append_to_dict(var, "entitylist", datas->entitylists);
    append_to_dict(var, "Sound", &datas->sounds);
    append_to_dict(var, "global", datas->global);
    append_to_dict(var, "Entity", &datas->entities);
    append_to_dict(var, "internal", get_internal_func());
}

static inline void reference_keys(dict_t **var, data_storage_t *datas)
{
    dict_t *new = NULL;

    append_to_dict(&new, "left", &datas->key.left);
    append_to_dict(&new, "right", &datas->key.right);
    append_to_dict(&new, "up", &datas->key.up);
    append_to_dict(&new, "down", &datas->key.down);
    append_to_dict(&new, "space", &datas->key.space);
    append_to_dict(var, "key", new);
}

#endif /* CMD_INITS_H_ */
