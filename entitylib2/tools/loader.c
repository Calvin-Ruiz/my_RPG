/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** loader.c
*/
#include <entitybase.h>
#include <data_storage.h>
#include <dirent.h>
#include <tools.h>
#include <fcntl.h>

char init_textures(data_storage_t *datas)
{
    DIR *d = opendir("textures");
    struct dirent *dirent;
    sfTexture *tmp = NULL;
    u_char i = 0;

    if (d == NULL)
        return (84);
    for (dirent = readdir(d); dirent; dirent = readdir(d)) {
        if (*dirent->d_name == '.')
            continue;
        for (i = 0; dirent->d_name[++i] != '.' &&
            dirent->d_name[i] != '\0'; i++);
        tmp = sfTexture_createFromFile(tmpcat("textures/", dirent->d_name), 0);
        dirent->d_name[i] = '\0';
        if (tmp)
            append_to_dict(&datas->textures, dirent->d_name, tmp);
    }
    closedir(d);
    return (0);
}

char init_sounds(data_storage_t *datas)
{
    DIR *d = opendir("sounds");
    struct dirent *dirent;

    if (d == NULL)
        return (84);
    for (dirent = readdir(d); dirent; dirent = readdir(d)) {
        if (*dirent->d_name == '.')
            continue;
        import_sound(datas, dirent->d_name);
    }
    closedir(d);
    return (0);
}
