/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** commands.c
*/

#include <executor.h>
#include <entitybase.h>
#include <entitylist.h>
#include <data_storage.h>
#include <data_io.h>
#include <dynamic_printer.h>

void append_to_list_cmd(char **args)
{
    if (args[2] == NULL)
        return;
    ((walk_t *) args[2])->next = *(walk_t **) args[1];
    *(walk_t **) args[1] = (walk_t *) args[2];
}

void change_of_map(char **args)
{
    data_storage_t *datas = get_data_storage();

    save_entities(datas->path, datas->mapname);
    for (uchar_t i = 0; ++i < datas->nb_entitylist;)
        clear_entitylist(datas->entitylists[i]);
    datas->mapname = args[1];
    datas->player->pos = (pos_t) {(sfVector2f) {(long) args[2],
        (long) args[3]}, (sfVector2f) {(long) args[2] + datas->player->size[0],
        (long) args[3] + datas->player->size[1]}};
    load_entities(datas->path, datas->mapname);
    load_tiles_from_file(datas->background, datas->mapname);
}

void sleep_cmd(char **args)
{
    sfSleep((sfTime) {(long) args[1]});
}

void put_in_log(char **arr)
{
    my_puterr("\e[37m> ");
    while (*++arr) {
        my_puterr(*arr);
        write(2, " ", 1);
    }
    my_puterr("\e[0m\n");
}

void operate(char **arr)
{
    if (arr[1] == NULL || arr[2] == NULL || arr[4] == NULL) {
        my_puterr("\e[94mIfError : nullptr received for variables\n\e[0m");
        return;
    }
    if (*(arr[3]) == '+')
        *(int *) arr[1] = *(int *) arr[2] + *(int *) arr[4];
    if (*(arr[3]) == '-')
        *(int *) arr[1] = *(int *) arr[2] - *(int *) arr[4];
    if (*(arr[3]) == '*')
        *(int *) arr[1] = *(int *) arr[2] * *(int *) arr[4];
    if (*(arr[3]) == '/')
        *(int *) arr[1] = *(int *) arr[2] / *(int *) arr[4];
    if (*(arr[3]) == '%')
        *(int *) arr[1] = *(int *) arr[2] % *(int *) arr[4];
}
