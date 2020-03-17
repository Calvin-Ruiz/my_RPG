/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** get_next_line.c
*/

#include <my_read.h>

char *fast_get_next_line(int fd)
{
    static int fd_old = 0;
    static long int pos = -2;
    static long int len = 0;
    static char *str = NULL;
    if (pos == -2 || fd != fd_old || str == NULL) {
        pos = -1;
        fd_old = fd;
        len = 0;
        str = my_read(fd, &len);
    }
    if (pos >= len && str) {
        free(str);
        str = NULL;
    }
    if (str == NULL)
        return (NULL);
    int pos2 = pos;
    while (++pos < len && str[pos] != '\n');
    str[pos] = '\0';
    return (str + pos2 + 1);
}
