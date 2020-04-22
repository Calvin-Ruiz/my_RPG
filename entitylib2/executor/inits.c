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
#include <cmd_inits.h>

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

    sub_init_vars(var, datas);
    reference_types_mouse_menu(var, datas);
    reference_keys(var, datas);
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
    append_to_dict(cmd, "operate", operate);
    init_external_cmds(cmd);
}

void init_executor(void)
{
    executor_t *executor = get_executor();

    init_cmd((dict_t **) &executor->cmd);
    init_vars((dict_t **) &executor->var);
    load_config(executor);
}
