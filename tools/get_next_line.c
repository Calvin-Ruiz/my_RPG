/*
** EPITECH PROJECT, 2019
** Global Tools
** File description:
** get_next_line.c
*/
#include "get_next_line.h"

char *my_stradd(char *first, char *last, int size, int from)
{
    int len = -1;
    int i = -1;
    char *str;

    while (first[++len] != '\0');
    len += size - from;
    str = malloc(len + 1);
    while (first[++i] != '\0')
        str[i] = first[i];
    last += from - i;
    do {
        str[i] = last[i];
    } while (++i < len);
    str[len] = '\0';
    free(first);
    return (str);
}

int find_newline(char *tmp, int last_newline, int size)
{
    while (++last_newline < size && tmp[last_newline] != '\n');
    if (last_newline < size || size != READ_SIZE)
        return (last_newline);
    return (-1);
}

static char *get_next_line_reader(int fd, char *tmp, int *size,
    int *newline_pos)
{
    char *str2 = malloc(1);
    int old_newline_pos = *newline_pos + 1;

    if (str2 == NULL)
        return (NULL);
    *str2 = '\0';
    while (1) {
        *newline_pos = find_newline(tmp, *newline_pos, *size);
        if (*newline_pos > -1) {
            tmp[*newline_pos] = '\0';
            return (my_stradd(str2, tmp, *size, old_newline_pos));
        }
        str2 = my_stradd(str2, tmp, *size, old_newline_pos);
        old_newline_pos = 0;
        *size = read(fd, tmp, *size);
    }
    return (NULL);
}

char *get_next_line(int fd)
{
    static char tmp[READ_SIZE];
    static int size = -2;
    static int newline_pos = -1;
    static int last_fd = -1;

    if (fd != last_fd) {
        last_fd = fd;
        size = read(fd, tmp, READ_SIZE);
    } else if (size != READ_SIZE && size <= newline_pos + 1) {
        size = read(fd, tmp, READ_SIZE);
        newline_pos = -1;
    }
    if (size < 1 || (size != READ_SIZE && size <= newline_pos + 1))
        return (NULL);
    return (get_next_line_reader(fd, tmp, &size, &newline_pos));
}
