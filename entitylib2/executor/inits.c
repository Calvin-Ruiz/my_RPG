/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** inits.c
*/

#include <executor.h>
#include <entitybase.h>
#include <data_storage.h>

static void create_sizeof(dict_t **var)
{
    dict_t *size = NULL;

    append_to_dict(&size, "sfVector2f", (long) sizeof(sfVector2f));
    append_to_dict(&size, "dict_t", (long) sizeof(dict_t));
    append_to_dict(&size, "entity_t", (long) sizeof(entity_t));
    append_to_dict(&size, "entitylist_t", (long) sizeof(entitylist_t));
    append_to_dict(&size, "menu_t", (long) sizeof(menu_t));
    append_to_dict(&size, "ptr", (long) sizeof(void *));
    append_to_dict(&size, "char", (long) sizeof(char));
    append_to_dict(&size, "double", (long) sizeof(double));
    append_to_dict(&size, "float", (long) sizeof(float));
    append_to_dict(&size, "short", (long) sizeof(short));
    append_to_dict(&size, "long", (long) sizeof(long));
    append_to_dict(&size, "int", (long) sizeof(int));
    append_to_dict(var, "sizeof", size));
}

static void init_vars(dict_t **var)
{
    data_storage_t *datas = get_data_storage();

    append_to_dict(var, "func", NULL);
    append_to_dict(var, "datas", datas);
    append_to_dict(var, "elist", datas->entitylists);
    append_to_dict(var, "entity", datas->entities);
    append_to_dict(var, "sound", datas->sounds);
    append_to_dict(var, "sbuff", datas->sound_buffs);
    append_to_dict(var, "textures", datas->textures);
    append_to_dict(var, "global", datas->global);
    append_to_dict(var, "local", NULL);
    create_sizeof(var);
}

static void init_cmd(dict_t **cmd)
{
    append_to_dict(cmd, "call", call_function);
    append_to_dict(cmd, "trace", set_traced_var_cmd);
    append_to_dict(cmd, "set", set_value);
    append_to_dict(cmd, "create_variable", set_value);
}

void init_executor(void)
{
    executor_t *executor = get_executor();

    init_cmd((dict_t **) &executor->cmd);
    init_vars((dict_t **) &executor->var);
    load_config(executor);
}
