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

void put_in_log(char **arr)
{
    while (*++arr) {
        my_puterr(*arr);
        write(2, " ", 1);
    }
    write(2, "\n", 1);
}

void operate(char **arr)
{
    if (arr[1] == NULL || arr[2] == NULL || arr[4] == NULL) {
        my_puterr("\e[94mIfError : nullptr received for variables\n\e[0m");
        return;
    }
    if (*(arr[3]) == '+')
        *(long *) arr[1] = *(long *) arr[2] + *(long *) arr[4];
    if (*(arr[3]) == '-')
        *(long *) arr[1] = *(long *) arr[2] - *(long *) arr[4];
    if (*(arr[3]) == '*')
        *(long *) arr[1] = *(long *) arr[2] * *(long *) arr[4];
    if (*(arr[3]) == '/')
        *(long *) arr[1] = *(long *) arr[2] / *(long *) arr[4];
    if (*(arr[3]) == '%')
        *(long *) arr[1] = *(long *) arr[2] % *(long *) arr[4];
}
