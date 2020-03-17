/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** tools.h
*/

#ifndef TOOLS_H_
#define TOOLS_H_

void no_update(void *ptr);
void default_destroy(void *ptr);
void my_putnbr(int nb);

static inline void my_putchar(char c)
{
    write(1, &c, 1);
}

static inline void my_putstr(char *str)
{
    int i = -1;

    while (str[++i]);
    write(1, str, i);
}

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

#endif /* TOOLS_H_ */
