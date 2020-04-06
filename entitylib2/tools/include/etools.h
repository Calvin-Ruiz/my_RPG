/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** etools.h
*/

#ifndef ETOOLS_H_
#define ETOOLS_H_

#include <tools.h>

void no_update(void *ptr);
void default_destroy(void *ptr);
char init_textures(data_storage_t *datas);

static inline void fast_nbr_in_str(char *end_of_str, int nbr, int len)
{
    while (nbr) {
        *(end_of_str--) = '0' + nbr % 10;
        nbr /= 10;
        len--;
    }
    while (len--)
        *(end_of_str--) = ' ';
}

static inline void *my_cpy(void *data, short len)
{
    char *raw = malloc(len);
    char *raw_data = data;
    short c = -1;

    if (raw) {
        while (++c < len)
            raw[c] = raw_data[c];
    }
    return (raw);
}

#endif /* ETOOLS_H */
