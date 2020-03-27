/*
** EPITECH PROJECT, 2019
** Global Tools
** File description:
** tools.h
*/

#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdlib.h>
#include <unistd.h>
#include <print_tools.h>

void *my_malloc(size_t size);
char **line_to_arr(char *str, const char sep);
char *tmpcat(char *str1, char *str2);
char **line_to_arr_mytmp(char *str, const char sep);

static inline char my_strcmp(const char *s1, const char *s2)
{
    while (*(s1++) == *(s2++) && s1[-1] != '\0');
    return (s1[-1] - s2[-1]);
}

static inline char *my_strdup(char *str)
{
    int len = -1;
    int i = -1;
    char *new = NULL;

    while (str[++len] != '\0');
    new = malloc(len + 1);
    if (new == NULL)
        return (NULL);
    while (i++ < len)
        new[i] = str[i];
    return (new);
}

#endif /* TOOLS_H_ */
