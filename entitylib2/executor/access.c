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
    my_puterr("\e[95mDictError : Failed to find '");
    my_puterr(name);
    my_puterr("'\n\e[0m");
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
    char **arr = line_to_arr_mytmp(name, '.') - 1;
    while (*++arr != NULL && var != NULL) {
        if (**arr == '+') {
            var = (rdict_t *) (((char *) var) + my_getnbr(*arr + 1));
            continue;
        }
        if (**arr == '[') {
            var = ((rdict_t **) var)[my_getnbr(*arr + 1)];
            continue;
        }
        if (**arr == '$') {
            var = get_chain((walk_t *) var, my_getnbr(*arr + 1));
            continue;
        }
        if (**arr == '@')
            var = (rdict_t *) (((char *) var) + get_in_struct(arr++));
        else
            var = get_from_rec_dict(var, *arr);
    }
    return (var);
}

void set_value(char **arr)
{
    if ((long) arr[-1] != 4)
        return;
    if ((long) arr[1] == UCHAR)
        *((u_char *) arr[2]) = (long) arr[3];
    if ((long) arr[1] == CHAR)
        *((char *) arr[2]) = (long) arr[3];
    if ((long) arr[1] == SHORT)
        *((short *) arr[2]) = (long) arr[3];
    if ((long) arr[1] == INT)
        *((int *) arr[2]) = (long) arr[3];
    if ((long) arr[1] == LONG)
        *((long *) arr[2]) = (long) arr[3];
    if ((long) arr[1] == PTR)
        *((void **) arr[2]) = (void *) arr[3];
    if ((long) arr[1] == FLOAT)
        *((float *) arr[2]) = get_float(arr[3]);
    if ((long) arr[1] == DOUBLE)
        *((double *) arr[2]) = get_double(arr[3]);
    if ((long) arr[1] == STR)
        *((char **) arr[2]) = my_tmpdup(arr[3]);
}

void create_variable(char **arr)
{
    dict_t **dict = (dict_t **) get_ptr_from_dict((dict_t *)
        get_executor()->var, "local");

    append_to_dict(dict, arr[2], my_malloc((long) arr[1]));
}
