/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** data_loader.c
*/
#include <entity.h>
#include <data_storage.h>
#include <converters.h>
#include <fast_get_next_line.h>
#include <tools.h>

void execute_file_contents(data_storage_t *datas, const char *filename)
{
    void (*func)(data_storage_t *datas, char **arr) = NULL;
    int fd = open(filename, O_RDONLY);
    char *str = fast_get_next_line(-1);
    char **arr = NULL;

    for (str = fast_get_next_line(fd); str; str = fast_get_next_line(fd)) {
        if (str[0] == '#' || str[0] == '\0')
            continue;
        arr = line_to_arr(str, ':');
        if ((long) arr[-1] == 1)
            continue;
        func = get_from_dict(datas->maker, *arr);
        if (func)
            func(datas, arr);
        free(arr - 1);
    }
    close(fd);
}

static int load_entitylist(int fd, entitylist_t *elist, data_storage_t *datas)
{
    short_to_raw_t nb_alive_entities;
    short_to_raw_t id_master;
    entity_t **entities = (entity_t **) datas->entities;
    entity_t *tmp;
    int i = -1;

    if (read(fd, nb_alive_entities.raw, 2) != 2)
        return (84);
    while (++i < nb_alive_entities.value) {
        if (read(fd, id_master.raw, 2) != 2)
            return (84);
        tmp = entities[id_master.value]->load(entities[id_master.value], fd);
        tmp->next = elist->next;
        elist->next = tmp;
    }
    return (0);
}

int load_all(char const *filename)
{
    data_storage_t *datas = get_data_storage();
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        write(2, "Failed to open save (read mode)\n", 36);
        return (84);
    }
    data_storage_to_raw_t datas_raw;
    if (read(fd, datas_raw.raw, 4) != 4) {
        close(fd);
        return (84);
    }
    datas->score = datas_raw.data.score;
    int ret = 0;
    int i = -1;
    while (++i < datas->nb_entitylist)
        ret = ret | load_entitylist(fd, datas->entitylists[i], datas);
    close(fd);
    return (ret);
}
