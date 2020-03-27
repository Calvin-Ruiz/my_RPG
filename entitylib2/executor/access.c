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

    while (*arr != NULL) {
        if (**arr == '+')
            return (((char *) var) + my_getnbr(*arr + 1));
        if (**arr == '$') {
            var = get_chain((walk_t *) var, my_getnbr(*(arr++) + 1));
            continue;
        }
        var = get_from_rec_dict(var, *(arr++));
        if (var == NULL)
            return (NULL);
    }
    return (var);
}
