/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** sound_manager.c
*/
#include <entitybase.h>
#include <data_storage.h>

int load_music(data_storage_t *data, const char *filename)
{
    data->music = sfMusic_createFromFile(filename);
    if (data->music == 0)
        return (84);
    sfMusic_setLoop(data->music, sfTrue);
    sfMusic_setVolume(data->music, data->volume);
    sfMusic_play(data->music);
    return (0);
}

void update_volume(data_storage_t *data)
{
    dict_t *sounds = data->sounds;

    sfMusic_setVolume(data->music, data->volume);
    while (sounds) {
        sfSound_setVolume(sounds->data, data->volume);
        sounds = sounds->next;
    }
}
