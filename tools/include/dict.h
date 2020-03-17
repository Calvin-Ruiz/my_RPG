/*
** EPITECH PROJECT, 2019
** Global Tools
** File description:
** dict.h
*/

#ifndef DICT_H_
#define DICT_H_

typedef struct my_dict {
    char *name;
    void *data;
    struct my_dict *next;
} dict_t;

void append_to_dict(dict_t **dict, char *name, void *data);
void *get_from_dict(dict_t *dict, char *name);
void **get_ptr_from_dict(dict_t *dict, char *name);
void destroy_dict(dict_t *dict, void (*destroy_content)());

#endif /* DICT_H_ */
