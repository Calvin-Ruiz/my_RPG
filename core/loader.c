/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** how_to_play.c
*/
#include <entitylib.h>
#include <fast_get_next_line.h>
#include <fcntl.h>

void my_init_textures_dict(data_storage_t *datas)
{
    int fd = open("textures/texture_list.txt", O_RDONLY);
    char *filename;
    int i = 0;
    datas->texture_dict = NULL;

    if (fd == -1) {
        datas->textures[0] = NULL;
        return;
    }
    filename = fast_get_next_line(fd);
    while (filename && *filename && i < datas->nb_textures) {
        datas->textures[i] = sfTexture_createFromFile(filename, NULL);
        append_to_dict(&datas->texture_dict, filename + 9,
            datas->textures[i++]);
        filename = fast_get_next_line(fd);
    }
    close(fd);
}
