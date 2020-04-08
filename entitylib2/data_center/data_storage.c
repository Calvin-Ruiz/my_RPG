/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** data_storage.c
*/
#include <entitylib.h>
#include <converters.h>

data_storage_t *get_data_storage(void)
{
    static data_storage_t storage;
    return (&storage);
}

static void init_data_storage_2(data_storage_t *datas)
{
    int_to_raw_t conv;
    float_to_raw_t conv2;
    int fd = open("saves/scoreboard.dat", O_RDONLY);

    datas->higher_score = 0;
    datas->volume = 100.f;
    if (fd != -1) {
        if (read(fd, conv.raw, 4) == 4)
            datas->higher_score = conv.value;
        if (read(fd, conv2.raw, sizeof(conv2.value)) == sizeof(conv2.value))
            datas->volume = conv2.value;
        close(fd);
    }
    if (datas->entitylists == NULL)
        return;
    fd = -1;
    while (++fd < datas->nb_entitylist)
        datas->entitylists[fd] = create_entitylist();
}

data_storage_t *init_data_storage(int nb_entitylist)
{
    data_storage_t *datas = get_data_storage();

    datas->sound_buffs = NULL;
    datas->sounds = NULL;
    datas->textures = NULL;
    datas->entities = NULL;
    datas->entitylists = malloc(sizeof(*(datas->entitylists)) * nb_entitylist);
    datas->nb_entitylist = nb_entitylist;
    datas->score = 0;
    datas->clock = sfClock_create();
    datas->is_alive = 1;
    datas->ask_command = 0;
    init_data_storage_2(datas);
    return (datas);
}

int check_data_storage_content(data_storage_t *datas)
{
    int check = (!datas->sounds) | (!datas->sound_buffs) | (!datas->textures) |
        (!datas->entities) | (!datas->entitylists) | (!datas->clock) |
        ((!datas->window) << 1);
    int i = -1;

    if (check)
        return (check);
    while (++i < datas->nb_entitylist)
        check = check | ((datas->entitylists[i] == NULL) << 2);
    return (check);
}

short append_saved(data_storage_t *datas, void *data)
{
    saved_t *saved = malloc(sizeof(saved_t));

    if (saved == NULL)
        return (-1);
    *saved = (saved_t) {datas->saved, data, datas->saved ? datas->saved->id + 1
        : 0};
    datas->saved = saved;
    return (saved->id);
}
