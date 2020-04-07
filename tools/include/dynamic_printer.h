/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2019
** File description:
** dynamic_printer.h
*/

#ifndef DYNAMIC_PRINTER_H_
#define DYNAMIC_PRINTER_H_

#include <dynamic_printer_tools.h>

static inline void put_line(char line_id)
{
    static char str[3] = {226, 148, 128};

    str[2] = line_id;
    write(1, str, 3);
}

static inline void my_move(unsigned short x, unsigned short y)
{
    const char *mvx = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
    const char *mvy = "\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v";

    write(1, "\e[H", 3);
    write(1, mvx, x >> 3);
    x = x & 7;
    while (x-- > 0)
        write(1, "\e[C", 3);
    write(1, mvy, y & 15);
    y = y >> 4;
    while (y-- > 0)
        write(1, mvy, 16);
}

static inline void relative_move(short x, short y)
{
    while (x-- > 0)
        write(1, "\e[C", 3);
    while (++x < 0)
        write(1, "\b", 1);
    while (y-- > 0)
        write(1, "\v", 1);
    while (++y < 0)
        write(1, "\e[A", 3);
}

static inline void draw_borders(const short x, const short y)
{
    char str2[300];

    for (int i = 1; ++i < 300;)
        str2[i] = ' ';
    str2[0] = 226;
    str2[1] = 148;
    str2[2] = 130;
    str2[x + 1] = 226;
    str2[x + 2] = 148;
    str2[x + 3] = 130;
    str2[x + 4] = '\n';
    write(1, "\n", 1);
    for (short i = 1; ++i < y;)
        write(1, str2, x + 5);
}

static inline void draw_cadre(short x, short y)
{
    const char clr[2] = {27, 'c'};
    char str[3] = {226, 148, 140};

    write(1, clr, 2);
    write(1, str, 3);
    str[2] = 128;
    for (short i = 1; ++i < x;)
        write(1, str, 3);
    str[2] = 144;
    write(1, str, 3);
    draw_borders(x, y);
    str[2] = 148;
    write(1, str, 3);
    str[2] = 128;
    for (short i = 1; ++i < x;)
        write(1, str, 3);
    str[2] = 152;
    write(1, str, 3);
}

#endif /* DYNAMIC_PRINTER_H_ */
