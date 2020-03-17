/*
** EPITECH PROJECT, 2019
** Global Tools
** File description:
** my_getnbr.h
*/

#ifndef MY_GETNBR_H_
#define MY_GETNBR_H_

static inline int add_char(int value, int add)
{
    if (value > 214748364) {
        return (0);
    } else if (value == 214748364 && add > 55) {
        return (0);
    }
    value *= 10;
    value += (add - 48);
    return (value);
}

static inline int my_getnbr(char const *str)
{
    int i = -1;
    int is_neg = 0;
    int value = 0;

    while (str[++i] > 57 || str[i] < 49) {
        is_neg += (str[i] == '-');
        if (str[i] != 45 && str[i] != 43 && str[i] != 48)
            return (0);
    }
    while (str[i] < 58 && str[i] > 47) {
        value = add_char(value, str[i]);
        if (value == 0)
            return (0);
        i++;
    }
    value = (is_neg & 1) ? -value : value;
    return (value);
}

#endif /* MY_GETNBR_H_ */
