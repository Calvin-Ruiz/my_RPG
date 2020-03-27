/*
** EPITECH PROJECT, 2019
** Global Tools
** File description:
** my_getnbr.h
*/

#ifndef MY_GETNBR_H_
#define MY_GETNBR_H_

static inline long my_getnbr(char const *str)
{
    short i = -1;
    unsigned char is_neg = 0;
    long value = 0;

    while (str[++i] > 57 || str[i] < 49) {
        is_neg += (str[i] == '-');
        if (str[i] != 45 && str[i] != 43 && str[i] != '0')
            return (0);
    }
    while (str[i] < 58 && str[i] > 47) {
        value = value * 10 + (str[i] - '0');
        if (value == 0)
            return (0);
        i++;
    }
    value = (is_neg & 1) ? -value : value;
    return (value);
}

#endif /* MY_GETNBR_H_ */
