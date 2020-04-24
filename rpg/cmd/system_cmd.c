/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** system_cmd.c
*/
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void read_cmd(char **arr)
{
    read(*(int *) arr[1], arr[2], (long) arr[3]);
}

void write_cmd(char **arr)
{
    write(*(int *) arr[1], arr[2], (long) arr[3]);
}

void putstr_cmd(char **arr)
{
    short i = -1;

    while (arr[2][++i] != '\0');
    write(*(int *) arr[1], arr[2], i);
}

void open_cmd(char **arr)
{
    *(int *) arr[1] = open(arr[2], O_RDWR | O_CREAT, (long) arr[3]);
}

void close_cmd(char **arr)
{
    close(*(int *) arr[1]);
}
