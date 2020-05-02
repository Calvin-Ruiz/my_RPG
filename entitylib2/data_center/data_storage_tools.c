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

static void destroy_entity_base(entity_t *self)
{
    const short max = self->size[2] * self->size[3];

    for (short i = -1; ++i < max;)
        sfSprite_destroy(self->sprite[i]);
    free(self->size);
    free(self->sprite);
    free(self);
}

void free_storage_content(data_storage_t *datas, int mask)
{
    datas->player->destroy(datas->player);
    destroy_dict(datas->sounds, sfSound_destroy);
    destroy_dict(datas->sound_buffs, sfSoundBuffer_destroy);
    destroy_dict(datas->textures, sfTexture_destroy);
    destroy_dict(datas->entities, destroy_entity_base);
    destroy_dict(datas->particle_lists, destroy_particle_list);
    if (datas->music)
        sfMusic_destroy(datas->music);
    if (mask & 4) {
        for (int i = 0; ++i < datas->nb_entitylist;)
            destroy_entitylist(datas->entitylists[i]);
    }
    sfClock_destroy(datas->entitylists[0]->clock);
    free(datas->entitylists[0]);
    if ((mask & 2) && datas->window != NULL)
        destroy_window(datas);
    free(datas->entitylists);
    sfClock_destroy(datas->clock);
    free(datas->background->vertex);
}
