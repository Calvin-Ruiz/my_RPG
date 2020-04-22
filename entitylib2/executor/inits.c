/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** inits.c
*/

#include <executor.h>
#include <entitybase.h>
#include <particle.h>
#include <data_storage.h>
#include <menu.h>

static void reference_sizeof(dict_t **var)
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
    append_to_dict(var, "sizeof", dict);
}

static void reference_types_mouse_menu(dict_t **var, data_storage_t *datas)
{
    dict_t *new = NULL;

    append_to_dict(&new, "uchar", (void *) UCHAR);
    append_to_dict(&new, "short", (void *) SHORT);
    append_to_dict(&new, "int", (void *) INT);
    append_to_dict(&new, "long", (void *) LONG);
    append_to_dict(&new, "float", (void *) FLOAT);
    append_to_dict(&new, "double", (void *) DOUBLE);
    append_to_dict(var, "type", new);
    new = NULL;
    append_to_dict(&new, "x", &datas->mouse.pos.x);
    append_to_dict(&new, "y", &datas->mouse.pos.y);
    append_to_dict(&new, "left", &datas->mouse.left);
    append_to_dict(&new, "wheel", &datas->mouse.wheel);
    append_to_dict(&new, "right", &datas->mouse.right);
    append_to_dict(var, "mouse", new);
    new = NULL;
    append_to_dict(&new, "main", &datas->main_menu);
    append_to_dict(&new, "pause", &datas->pause_menu);
    append_to_dict(var, "menu", new);
}

static void init_vars(dict_t **var)
{
    data_storage_t *datas = get_data_storage();
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
    reference_types_mouse_menu(var, datas);
    append_to_dict(var, "particle_list", datas->particle_lists);
    append_to_dict(var, "Particle_emitter", &datas->particle_emitters);
    append_to_dict(var, "color", get_sf_colors());
    append_to_dict(var, "Player", &datas->player);
    append_to_dict(var, "func", NULL);
    append_to_dict(var, "local", NULL);
}

static void init_cmd(dict_t **cmd)
{
    append_to_dict(cmd, "call", call_function);
    append_to_dict(cmd, "trace", set_traced_var_cmd);
    append_to_dict(cmd, "tracer", trace_thread);
    append_to_dict(cmd, "set", set_value);
    append_to_dict(cmd, "create_variable", create_variable);
    append_to_dict(cmd, "thread", thread_cmd);
    append_to_dict(cmd, "append", append_to_list_cmd);
    append_to_dict(cmd, "new", new_entity);
    append_to_dict(cmd, "log", put_in_log);
    append_to_dict(cmd, "sleep", sleep_cmd);
    append_to_dict(cmd, "append_particle", append_particle_cmd);
    append_to_dict(cmd, "create_particle_emitter", create_particle_emitter_cmd);
    append_to_dict(cmd, "if", execute_if_true);
    init_external_cmds(cmd);
}

void init_executor(void)
{
    executor_t *executor = get_executor();

    init_cmd((dict_t **) &executor->cmd);
    init_vars((dict_t **) &executor->var);
    load_config(executor);
}
