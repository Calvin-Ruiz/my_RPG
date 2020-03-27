/*
** EPITECH PROJECT, 2019
** Global Tools
** File description:
** print_tools.h
*/

#ifndef PRINT_TOOLS_H_
#define PRINT_TOOLS_H_

void rec_putnbr(long nb);

static inline void my_putchar(char c)
{
    write(1, &c, 1);
}

static inline void my_putstr(char *str)
{
    int len = -1;

    while (str[++len] != '\0');
    write(1, str, len);
}

static inline void my_puterr(char *str)
{
    int len = -1;

    while (str[++len] != '\0');
    write(2, str, len);
}

static inline void my_putnbr(long nb)
{
    if (nb < 0) {
        nb = -nb;
        my_putchar('-');
    }
    if (nb >= 10) {
        if (nb >= 100)
            rec_putnbr(nb / 100);
        my_putchar('0' + (nb / 10) % 10);
    }
    my_putchar('0' + nb % 10);
}

#endif /* PRINT_TOOLS_H_ */
