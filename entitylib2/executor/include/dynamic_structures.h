/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** dynamic_structures.h
*/

#ifndef DYNAMIC_STRUCTURES_H_
#define DYNAMIC_STRUCTURES_H_

#include <my_getnbr.h>

typedef union universal_data {
    char c;
    short s;
    int i;
    long l;
    float f;
    double d;
    void *ptr;
} universal_data_t;

static inline void *get_float_or_double(char *str)
{
    universal_data_t uni;

    switch (*str) {
        case 'f':
            uni.f = get_float(str + 1);
            break;
        case 'd':
            uni.d = get_double(str + 1);
            break;
        default:
            uni.ptr = NULL;
    }
    return (uni.ptr);
}

static inline void *eval_arg(char *str, executor_t *executor)
{
    static void *out = NULL;

    switch (*str) {
        case '$':
            out = get_data(str + 1, executor->var);
            break;
        case '=':
            out = (char *) my_getnbr(str + 1);
            break;
        case '&':
            out = get_from_dict((dict_t *) executor->cmd, str + 1);
            break;
        case '@':
            out = (char *) (get_args() + my_getnbr(str + 1));
            break;
        case '~':
            out = get_float_or_double(str + 1);
            break;
    }
    return (&out);
}

static inline short get_data_len(char *str, dict_t *var)
{
    long dlen = 0;

    if (str[0] == 'r' && str[1] == 'a' && str[2] == 'w')
        dlen = my_getnbr(str + 3);
    else
        dlen = (long) get_from_dict((dict_t *) get_from_dict(var, "sizeof"),
            str);
    if (dlen == 0) {
        my_puterr("\e[35mNullComponentLength : ");
        my_puterr("One component of dynamic struct have a lenght of 0.\e[0m\n");
    }
    return ((short) dlen);
}

static inline void insert_data(char **ptr, short dlen, char *data)
{
    while (dlen-- > 0)
        *((*ptr)++) = *(data++);
}

#endif /* DYNAMIC_STRUCTURES_H_ */
