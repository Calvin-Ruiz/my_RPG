/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** sound_manager.c
*/
#include <entitybase.h>
#include <data_storage.h>
#include <tools.h>
#include <dynamic_printer.h>

int load_music(data_storage_t *data, const char *filename)
{
    data->music = sfMusic_createFromFile(filename);
    if (data->music == NULL)
        return (84);
    sfMusic_setLoop(data->music, sfTrue);
    sfMusic_setVolume(data->music, data->volume);
    sfMusic_play(data->music);
    return (0);
}

void update_volume(data_storage_t *data)
{
    dict_t *sounds = data->sounds;

    while (sounds) {
        sfSound_setVolume(sounds->data, data->volume);
        sounds = sounds->next;
    }
}

void set_music_cmd(char **arr)
{
    data_storage_t *data = get_data_storage();
    if (arr[1] != NULL) {
        my_puterr("\e[37;3m");
        data->music = sfMusic_createFromFile(arr[1]);
        if (data->music == NULL) {
            my_puterr("\e[0;95mMusicError : Failed to load '");
            my_puterr(arr[1]);
            my_puterr("' music.\n\e[0m");
            return;
        }
        sfMusic_setLoop(data->music, sfTrue);
        sfMusic_play(data->music);
        my_puterr("\e[0m");
    }
    if (data->music == NULL)
        return;
    if ((long) arr[2] > 100)
        sfMusic_setVolume(data->music, 100);
    else if ((long) arr[2] >= 0)
        sfMusic_setVolume(data->music, (long) arr[1]);
}

void set_sound_volume_cmd(char **arr)
{
    data_storage_t *datas = get_data_storage();

    if ((ulong_t) arr[1] > 100)
        datas->volume = 100;
    else
        datas->volume = (long) arr[1];
    update_volume(datas);
}
