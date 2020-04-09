/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** function.c
*/

#include <executor.h>
#include <entitybase.h>
#include <entitylist.h>
#include <data_storage.h>
#include <my_getnbr.h>
#include <fcntl.h>
#include <my_read.h>

char **get_args(void)
{
    static char *args[32];

    return (args);
}

void call_function(char **arr)
{
    char **args = get_args() - 1;
    func_t *func = get_from_dict((dict_t *)
        get_from_rec_dict(get_executor()->var, "func"), arr[1]);

    for (u_char i = 0; ++i < (long) arr[-1];)
        args[i] = arr[i];
    while (func) {
        ((void (*)(char **)) *func->arr)(func->arr);
        func = func->next;
    }
}

void new_entity(char **arr)
{
    if (arr[1] == NULL || arr[2] == NULL) {
        my_puterr("\e[35mInstanciateError : nullptr in arguments.\n\e[0m");
        return;
    }
    append_to_entitylist(*get_data_storage()->entitylists, (entitylist_t *)
        arr[1], ((entity_t *) arr[2])->new(arr + 2));
}

static void build_func_line(func_t **func, char *line, executor_t *executor)
{
    func_t *new = malloc(sizeof(func_t));
    char **arr = line_to_arr(line, ' ');

    if (new == NULL || arr == (char **) sizeof(char *))
        return;
    new->next = *func;
    *new->arr = get_from_dict((dict_t *) executor->cmd, *arr);
    eval_args(arr, executor);
    new->arr = arr;
    if (*new->arr)
        *func = new;
}

void build_function(char *filename, executor_t *executor)
{
    int fd = open(tmpcat("config/", filename), O_RDONLY);
    long len = 0;
    char *str = my_read(fd, &len);
    char **arr;
    short i = -1;
    func_t *func = NULL;

    if (str == NULL)
        return;
    close(fd);
    str[len] = '\0';
    arr = line_to_arr(str, '\n');
    for (short i = (long) arr[-1]; i-- > 0;) {
        if (*(arr[i]) != '#' && *(arr[i]) != '\0')
            build_func_line(&func, arr[i], executor);
    }
    while (filename[++i] != '.');
    filename[i] = '\0';
    append_to_dict((dict_t **) get_ptr_from_dict((dict_t *) executor->var,
        "func"), filename, func);
}
