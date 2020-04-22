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
#include <function.h>

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
    char *farg[64] = {0};
    for (u_char i = 0; ++i < (long) arr[-1];)
        args[i] = arr[i];
    my_puterr("\e[92m>---- START ");
    my_puterr(arr[1]);
    my_puterr(" ----<\n\e[0m");
    if (func == NULL)
        my_puterr("\e[31mCallError : This function is not defined.\n");
    while (func) {
        farg[0] = (char *) (long) func->data->is_complete;
        for (short i = -1; ++i < func->data->is_complete;)
            farg[i + 1] = func->data[i].is_complete ?
                func->data[i].data : get_in_args(func->data[i].data);
        ((void (*)(char **)) farg[1])(farg + 1);
        func = func->next;
    }
    my_puterr("\e[92m<---- END ---->\n\e[0m");
}

void execute_if_true(char **arr)
{
    char result = 0;

    if (arr[1] == NULL || arr[3] == NULL) {
        my_puterr("\e[94mIfError : nullptr received for variables\n\e[0m");
        return;
    }
    if (arr[2][0] == '<')
        result = *(long *) arr[1] < *(long *) arr[3];
    if (arr[2][0] == '>')
        result = *(long *) arr[1] > *(long *) arr[3];
    if (arr[2][0] == '=')
        result = *(long *) arr[1] == *(long *) arr[3];
    if (result ^ (arr[2][1] == '!'))
        ((void (*)(char **arr)) arr[4])(arr + 4);
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

void build_function(char *filename, executor_t *executor)
{
    int fd = open(tmpcat("config/", filename), O_RDONLY);
    long len = 0;
    char *str = my_read(fd, &len);
    char **arr = line_to_arr(str, '\n');
    short j = -1;
    func_t *func = NULL;

    if (arr == NULL)
        return;
    close(fd);
    for (short i = (long) arr[-1]; i-- > 0;) {
        if (*(arr[i]) != '#' && *(arr[i]) != '\0')
            build_func_line(&func, arr[i], executor);
    }
    while (filename[++j] != '.');
    filename[j] = '\0';
    append_to_dict((dict_t **) get_ptr_from_dict((dict_t *) executor->var,
        "func"), filename, func);
    free(arr - 1);
    free(str);
}
