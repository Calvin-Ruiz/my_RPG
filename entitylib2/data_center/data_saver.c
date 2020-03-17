/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** data_saver.c
*/
#include <entitybase.h>
#include <data_storage.h>
#include <converters.h>

static void save_entity(int fd, entity_t *entity, entity_t **entities)
{
    short_to_raw_t id_master;

    id_master.value = -1;
    while (entity->size != entities[++id_master.value]->size);
    write(fd, id_master.raw, 2);
    entity->save(entity, fd);
}

static void save_entitylist(int fd, entitylist_t *elist, entity_t **entities)
{
    entity_t *entity = elist->next;
    short_to_raw_t nbr_alive_entities;

    nbr_alive_entities.value = 0;
    while (entity) {
        nbr_alive_entities.value++;
        entity = entity->next;
    }
    write(fd, nbr_alive_entities.raw, 2);
    entity = elist->next;
    while (entity) {
        save_entity(fd, entity, entities);
        entity = entity->next;
    }
}

int save_all(const char *filename)
{
    data_storage_t *datas = get_data_storage();
    entity_t **entities = datas->entities;
    entitylist_t **elists = datas->entitylists;
    int fd = open(filename, O_WRONLY | O_CREAT, 0666);

    if (fd == -1) {
        write(2, "Failed to open save (write mode)\n", 37);
        return (84);
    }
    data_storage_to_raw_t datas_raw;
    datas_raw.data.score = datas->score;
    write(fd, datas_raw.raw, 4);
    int i = -1;
    while (++i < datas->nb_entitylist)
        save_entitylist(fd, elists[i], entities);
    close(fd);
    return (0);
}
