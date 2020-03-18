/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** loader.c
*/
#include <entitylib.h>
#include <fast_get_next_line.h>
#include <fcntl.h>

void my_init_textures(data_storage_t *datas)
{
    int fd = open("config/textures.txt", O_RDONLY);
    char *filename = fast_get_next_line(-1);
    sfTexture *tmp = NULL;

    if (fd == -1)
        return;
    filename = fast_get_next_line(fd);
    while (filename && *filename) {
        tmp = sfTexture_createFromFile(filename, NULL);
        if (tmp)
            append_to_dict(&datas->textures, filename + 9, tmp);
        filename = fast_get_next_line(fd);
    }
    close(fd);
}
