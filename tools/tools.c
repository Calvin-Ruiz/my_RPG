/*
** EPITECH PROJECT, 2019
** Global Tools
** File description:
** tools.c
*/
#include <stdlib.h>
#include <unistd.h>

void *my_malloc(size_t size)
{
    static char buffer[1024*64];
    static long int pos = 0;

    pos += size;
    return (buffer + pos - size);
}

char **line_to_arr(char *str, const char sep)
{
    int i = -1;
    long int nargs = 3;
    char **arr;
    char **sav;
    if (str == NULL)
        return (NULL);
    for (int i = -1; str[++i] != '\0';)
        nargs += str[i] == sep;
    arr = malloc(sizeof(char *) * nargs);
    if (arr == NULL)
        return (NULL);
    sav = arr;
    *(arr++) = (char *) (nargs - 2);
    while (str[i] != '\0') {
        *(arr++) = str + i;
        while (str[i] != '\0' && str[i++] != sep);
        str[i - (str[i] != '\0')] = '\0';
    }
    *arr = NULL;
    return (sav + 1);
}
