/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** access.c
*/

#include <executor.h>
#include <tools.h>
#include <my_getnbr.h>

rdict_t *get_from_rec_dict(rdict_t *dict, char *name)
{
    while (dict) {
        if (my_strcmp(name, dict->name)) {
            dict = dict->next;
            continue;
        }
        return (dict->dict);
    }
    return (NULL);
}

static void *get_chain(walk_t *walker, int nb)
{
    while (nb-- && walker)
        walker = walker->next;
    return (walker);
}

void *get_data(char *name, rdict_t *var)
{
    char **arr = line_to_arr_mytmp(name, '.');

    while (*arr != NULL && var != NULL) {
        if (**arr == '+') {
            var = (rdict_t *) (((char *) var) + my_getnbr(*arr + 1));
            continue;
        }
        if (**arr == '[') {
            var = *((rdict_t **) (((char *) var) + my_getnbr(*arr + 1)));
            continue;
        }
        if (**arr == '$') {
            var = get_chain((walk_t *) var, my_getnbr(*(arr++) + 1));
            continue;
        }
        var = get_from_rec_dict(var, *(arr++));
    }
    return (var);
}

void set_value(char **arr, rdict_t *var)
{
    void *data = get_data(arr[2], var);

    if (data == NULL)
        return;
    if (my_strcmp("char", arr[1]) == 0)
        *((char *) data) = my_getnbr(arr[3]);
    if (my_strcmp("short", arr[1]) == 0)
        *((short *) data) = my_getnbr(arr[3]);
    if (my_strcmp("int", arr[1]) == 0)
        *((int *) data) = my_getnbr(arr[3]);
    if (my_strcmp("long", arr[1]) == 0)
        *((long *) data) = my_getnbr(arr[3]);
    if (my_strcmp("float", arr[1]) == 0)
        *((float *) data) = my_getnbr(arr[3]);
    if (my_strcmp("double", arr[1]) == 0)
        *((double *) data) = my_getnbr(arr[3]);
    if (my_strcmp("ptr", arr[1]) == 0)
        *((void **) data) = get_data(arr[3], var);
}

void create_variable(char **arr, rdict_t *var)
{
    dict_t **dict = (dict_t **) get_ptr_from_dict((dict_t *) var, "local");

    append_to_dict(dict, arr[2], my_malloc((long) get_data(
        tmpcat("sizeof.", arr[1]), var)));
}
