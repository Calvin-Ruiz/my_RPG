/*
** EPITECH PROJECT, 2019
** Global Tools
** File description:
** my_read.h
*/

#ifndef MY_READ_H_
#define MY_READ_H_

#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DATALEN 4096

typedef struct strchain {
    struct strchain *next;
    char *data;
} strchain_t;

char *my_read(const int port, long int *full_size);

#endif /* MY_READ_H_ */
