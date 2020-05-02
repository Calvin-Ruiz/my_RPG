/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** cmd_uninit.h
*/

#ifndef CMD_UNINIT_H_
#define CMD_UNINIT_H_

static inline void destroy_dict_rec_once(dict_t *dict,
    void (*destroyer)())
{
    void *tmp;

    while (dict) {
        tmp = dict->next;
        destroy_dict(dict->data, destroyer);
        free(dict->name);
        free(dict);
        dict = tmp;
    }
}

static inline void cmd_uninit(void)
{
    executor_t *executor = get_executor();
    dict_t *var = (dict_t *) executor->var;

    destroy_dict((dict_t *) executor->cmd, NULL);
    destroy_dict(get_from_dict(var, "thread"), sfThread_destroy);
    destroy_dict(get_from_dict(var, "type"), NULL);
    destroy_dict(get_from_dict(var, "mouse"), NULL);
    destroy_dict(get_from_dict(var, "sizeof"), NULL);
    destroy_dict_rec_once(get_from_dict(var, "struct"), NULL);
    destroy_dict(get_from_dict(var, "local"), NULL);
    destroy_dict(get_from_dict(var, "func"), destroy_func);
    destroy_dict(get_from_dict(var, "color"), NULL);
    destroy_dict(get_from_dict(var, "menu"), destroy_menu);
    destroy_dict(get_from_dict(var, "internal"), NULL);
    destroy_dict(get_from_dict(var, "key"), NULL);
    destroy_dict(var, NULL);
    executor->cmd = NULL;
    executor->var = NULL;
}

#endif /* CMD_UNINIT_H_ */
