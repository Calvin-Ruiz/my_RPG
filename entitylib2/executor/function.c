/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** function.c
*/

#include <executor.h>
#include <tools.h>
#include <my_getnbr.h>
#include <fcntl.h>
#include <my_read.h>

static void exec_function(char **arr, rdict_t *var, func_t *func)
{
    const unsigned char nb_args = (long) func->arr[-1];
    unsigned char pos = -1;
    char **exe = ((char **) malloc(sizeof(char *) * (nb_args + 2))) + 1;
    unsigned char nb;

    if (exe == (char **) sizeof(char *))
        return;
    exe[-1] = func->arr[-1];
    while (func->arr[++pos] != NULL) {
        if (*(func->arr[pos]) == '$') {
            nb = my_getnbr(func->arr[pos] + 1) + 1;
            exe[pos] = (nb < (long) arr[-1]) ? arr[nb] : NULL;
        } else
            exe[pos] = func->arr[pos];
    }
    exe[pos] = NULL;
    func->cmd(exe, var);
    free(exe - 1);
}

void call_function(char **arr, rdict_t *var)
{
    func_t *func = get_from_dict((dict_t *) get_from_rec_dict(var, "func"),
        arr[1]);

    while (func) {
        exec_function(arr, var, func);
        func = func->next;
    }
}

static void build_func_line(func_t **func, char *line, executor_t *executor)
{
    func_t *new = malloc(sizeof(func_t));
    char **arr = line_to_arr(line, ' ');

    if (new == NULL || arr == (char **) sizeof(char *))
        return;
    new->next = *func;
    new->cmd = get_from_dict((dict_t *) executor->cmd, arr[0]);
    new->arr = arr;
    if (new->cmd)
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
    str[len] = '\0';
    arr = line_to_arr(str, '\n');
    for (short i = (long) arr[-1]; i-- > 0;) {
        if (*(arr[i]) != '#' && *(arr[i]) != '\0')
            build_func_line(&func, arr[i], executor);
    }
    close(fd);
    while (filename[++i] != '.');
    filename[i] = '\0';
    append_to_dict((dict_t **) get_ptr_from_dict((dict_t *) executor->var,
        "func"), filename, func);
}
