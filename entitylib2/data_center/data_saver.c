/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** data_saver.c
*/
#include <entitybase.h>
#include <data_storage.h>
#include <converters.h>
#include <tools.h>

static void save_entitylist(int fd, entitylist_t *elist)
{
    entity_t *entity = elist->next;
    short_to_raw_t nbr_alive_entities;

    nbr_alive_entities.value = 0;
    while (entity) {
        if (entity->save)
            nbr_alive_entities.value++;
        entity = entity->next;
    }
    write(fd, nbr_alive_entities.raw, 2);
    entity = elist->next;
    while (entity) {
        if (entity->save) {
            write(fd, (char *) &entity->id, 2);
            entity->save(entity, fd);
        }
        entity = entity->next;
    }
}

char save_tags(char *path)
{
    int fd = open(tmpcat(path, "tags.dat"), O_WRONLY | O_CREAT, 0666);
    saved_t *saved = get_data_storage()->saved;
    ushort_t size = 0;

    if (fd == -1) {
        my_puterr("Failed to open tags file (write mode)\n");
        return (84);
    }
    while (saved) {
        write(fd, (char *) &saved->id, 2);
        size = *(ushort_t *) saved->data;
        write(fd, (char *) saved->data, size + 2);
        saved = saved->next;
    }
    close(fd);
    return (0);
}

char save_entities(char *path, char *map)
{
    data_storage_t *datas = get_data_storage();
    entitylist_t **elists = datas->entitylists;
    int fd = open(tmpcat(tmpcat(path, map), ".dat"), O_WRONLY | O_CREAT, 0666);
    int i = 0;

    if (fd == -1) {
        my_puterr("Failed to open map file (write mode)\n");
        return (84);
    }
    while (++i < datas->nb_entitylist)
        save_entitylist(fd, elists[i]);
    close(fd);
    return (0);
}
