/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** access.c
*/

#include <executor.h>
#include <my_getnbr.h>
#include <entitybase.h>

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

void set_value(char **arr)
{
    if (my_strcmp("vec", arr[1]) == 0 && (long) arr[-1] == 5)
        *((sfVector2f *) arr[2]) = (sfVector2f) {(long) arr[3], (long) arr[4]};
    if ((long) arr[-1] != 4)
        return;
    if (my_strcmp("char", arr[1]) == 0)
        *((char *) arr[2]) = (long) arr[3];
    if (my_strcmp("short", arr[1]) == 0)
        *((short *) arr[2]) = (long) arr[3];
    if (my_strcmp("int", arr[1]) == 0)
        *((int *) arr[2]) = (long) arr[3];
    if (my_strcmp("long", arr[1]) == 0)
        *((long *) arr[2]) = (long) arr[3];
    if (my_strcmp("float", arr[1]) == 0)
        *((float *) arr[2]) = (long) arr[3];
    if (my_strcmp("double", arr[1]) == 0)
        *((double *) arr[2]) = (long) arr[3];
    if (my_strcmp("raw64", arr[1]) == 0)
        *((void **) arr[2]) = (void *) arr[3];
}

void create_variable(char **arr)
{
    dict_t **dict = (dict_t **) get_ptr_from_dict((dict_t *)
        get_executor()->var, "local");

    append_to_dict(dict, arr[2], my_malloc((long) arr[1]));
}
