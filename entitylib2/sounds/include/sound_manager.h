/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** sound_manager.h
*/

#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

int load_music(data_storage_t *data, const char *filename);
void update_volume(data_storage_t *data);
void set_music_cmd(char **arr);
void set_sound_volume_cmd(char **arr);

#endif /* SOUND_MANAGER_H_ */
