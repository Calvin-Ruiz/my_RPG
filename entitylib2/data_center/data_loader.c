/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** data_loader.c
*/
#include <entity.h>
#include <entitylist.h>
#include <data_storage.h>
#include <converters.h>
#include <fast_get_next_line.h>
#include <tools.h>

static char load_entitylist(int fd, entitylist_t *elist, data_storage_t *datas)
{
    short_to_raw_t nb_alive_entities;
    short_to_raw_t id_master;
    entitylist_t *display = *datas->entitylists;
    dict_t *entity = NULL;
    int i = -1;

    if (read(fd, nb_alive_entities.raw, 2) != 2)
        return (84);
    while (++i < nb_alive_entities.value) {
        if (read(fd, id_master.raw, 2) != 2)
            return (84);
        for (entity = datas->entities; entity && ((entity_t *) entity->data)->id
            != id_master.value; entity = entity->next);
        if (entity == NULL)
            return (84);
        append_to_entitylist(display, elist,
            ((entity_t *) entity->data)->load(entity->data, fd));
    }
    return (0);
}

char load_tags(char *path)
{
    int fd = open(tmpcat(path, "tags.dat"), O_RDONLY);
    saved_t **saved = &get_data_storage()->saved;
    char buf[2048];
    saved_t *new = NULL;
    char *data = NULL;
    for (short size = read(fd, buf, 4); size == 4; size = read(fd, buf, 4)) {
        data = malloc((*(short *) (buf + 2)) + 2);
        size += read(fd, data + 2, *(short *) (buf + 2));
        if (size != (*(short *) (buf + 2)) + 4) {
            my_puterr("\e[91mCorruptionError : tags file is corrupted\n\e[0m");
            return (84);
        }
        new = malloc(sizeof(saved_t));
        *(short *) data = *(short *) (buf + 2);
        *new = (saved_t) {NULL, data, *(short *) buf};
        *saved = new;
        saved = &new->next;
    }
    close(fd);
    return (0);
}

char load_entities(char *path, char *map)
{
    data_storage_t *datas = get_data_storage();
    char ret = 0;
    int fd = open(tmpcat(tmpcat(path, map), ".dat"), O_RDONLY);
    int i = 0;

    if (fd == -1) {
        my_puterr("\e[95mFailed to open map file (read mode)\n\e[0m");
        return (84);
    }
    while (++i < datas->nb_entitylist)
        ret = ret | load_entitylist(fd, datas->entitylists[i], datas);
    close(fd);
    return (ret);
}
