/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** commands.c
*/

#include <executor.h>
#include <SFML/System.h>

void append_to_list_cmd(char **args)
{
    if (args[2] == NULL)
        return;
    ((walk_t *) args[2])->next = *(walk_t **) args[1];
    *(walk_t **) args[1] = (walk_t *) args[2];
}

void sleep_cmd(char **args)
{
    sfSleep((sfTime) {(long) args[1]});
}
