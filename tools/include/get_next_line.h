/*
** EPITECH PROJECT, 2019
** Global Tools
** File description:
** get_next_line.h
*/

#ifndef GET_NEXT_LINE_H_
#define GET_NEXT_LINE_H_

#include <stdlib.h>
#include <unistd.h>

char *get_next_line(int fd);

#ifndef READ_SIZE
#define READ_SIZE 512
#endif /* READ_SIZE */

typedef struct strchain {
    char *data;
    struct strchain *next;
} strchain_t;

#endif /* GET_NEXT_LINE_H_ */
