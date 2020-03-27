/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2019
** File description:
** dynamic_printer_tools.h
*/

#ifndef DYNAMIC_PRINTER_TOOLS_H_
#define DYNAMIC_PRINTER_TOOLS_H_

enum {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYAN,
    WHITE,
    FOREGROUND_DARK = 30,
    BACKGROUND_DARK = 40,
    FOREGROUND_LIGHT = 90,
    BACKGROUND_LIGHT = 100,
};

enum {
    CLEAR = 48,
    GRAS,
    DARK,
    ITALIQUE,
    UNDERLINE,
    CLIGNOTANT,
    DEPRECATED_CLIGNOTANT,
    INVERTED,
    UNVISIBLE,
    BARRE,
};

static inline void my_set_color(char color)
{
    char str[3] = "00m";

    write(1, "\e[", 2);
    if (color > 99) {
        write(1, "1", 1);
        color -= 100;
    }
    str[0] += color / 10;
    str[1] += color % 10;
    write(1, str, 3);
}

static inline void my_set_effect(char effect)
{
    char str[4] = "\e[#m";

    str[2] = effect;
    write(1, str, 4);
}

static inline void my_unset_effect(char effect)
{
    char str[5] = "\e[2#m";

    str[3] = effect;
    write(1, str, 5);
}

#endif /* DYNAMIC_PRINTER_TOOLS_H_ */
