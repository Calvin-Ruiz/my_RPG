/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** data_storage_tools.c
*/
#include <entitylib.h>
#include <converters.h>
#include <tools.h>

void import_sound(data_storage_t *datas, char *name)
{
    sfSoundBuffer *tmp = sfSoundBuffer_createFromFile(tmpcat("sounds/", name));
    sfSound *tmp2 = sfSound_create();
    u_char i = 0;

    if (tmp == NULL)
        return;
    if (tmp2 == NULL) {
        sfSoundBuffer_destroy(tmp);
        return;
    }
    sfSound_setBuffer(tmp2, tmp);
    sfSound_setVolume(tmp2, datas->volume);
    for (i = 0; name[i] != '.' &&
        name[i] != '\0'; i++);
    name[i] = '\0';
    append_to_dict(&datas->sound_buffs, name, tmp);
    append_to_dict(&datas->sounds, name, tmp2);
}

void update_all(data_storage_t *datas)
{
    int i = -1;

    while (++i < datas->nb_entitylist)
        datas->entitylists[i]->update(datas->entitylists[i], datas);
}

void save_higher_score(data_storage_t *datas)
{
    int_to_raw_t conv;
    float_to_raw_t conv2;

    if (datas->higher_score < datas->score)
        datas->higher_score = datas->score;
    conv.value = datas->higher_score;
    conv2.value = datas->volume;
    int fd = open("saves/scoreboard.dat", O_WRONLY | O_CREAT, 0666);
    if (fd != -1) {
        write(fd, conv.raw, 4);
        write(fd, conv2.raw, sizeof(conv2.value));
        close(fd);
    }
}

static void auto_destroy(entity_t *self)
{
    self->destroy(self);
}

void free_storage_content(data_storage_t *datas, int mask)
{
    int i = -1;

    destroy_dict(datas->sounds, sfSound_destroy);
    destroy_dict(datas->sound_buffs, sfSoundBuffer_destroy);
    destroy_dict(datas->textures, sfTexture_destroy);
    destroy_dict(datas->entities, auto_destroy);
    if (mask & 4) {
        while (++i < datas->nb_entitylist)
            destroy_entitylist(datas->entitylists[i]);
    }
    if ((mask & 2) && datas->window != NULL)
        destroy_window(datas);
    save_higher_score(datas);
    free(datas->entitylists);
    sfClock_destroy(datas->clock);
}
