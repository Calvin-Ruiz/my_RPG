/*
** EPITECH PROJECT, 2019
** Global Tools
** File description:
** dict.c
*/
#include <stdlib.h>
#include <unistd.h>
#include <tools.h>
#include <dict.h>

void append_to_dict(dict_t **dict, char *name, void *data)
{
    dict_t *new = malloc(sizeof(dict_t));

    if (new) {
        new->next = *dict;
        new->name = my_strdup(name);
        new->data = data;
        *dict = new;
    }
}


char *get_name_from_dict(dict_t *dict, void *data)
{
    while (dict) {
        if (data != dict->data) {
            dict = dict->next;
            continue;
        }
        return (dict->name);
    }
    return (NULL);
}

void *get_from_dict(dict_t *dict, char *name)
{
    while (dict) {
        if (my_strcmp(name, dict->name)) {
            dict = dict->next;
            continue;
        }
        return (dict->data);
    }
    return (NULL);
}

void **get_ptr_from_dict(dict_t *dict, char *name)
{
    while (dict) {
        if (my_strcmp(name, dict->name)) {
            dict = dict->next;
            continue;
        }
        return (&dict->data);
    }
    return (NULL);
}

void destroy_dict(dict_t *dict, void (*destroy_content)())
{
    void *tmp;

    while (dict) {
        tmp = dict->next;
        if (destroy_content)
            destroy_content(dict->data);
        free(dict->name);
        free(dict);
        dict = tmp;
    }
}
