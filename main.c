/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** main.c
*/
#include <entitylib.h>
#include <main.h>

void my_closure(data_storage_t *datas)
{
    sfRenderWindow_close(datas->window);
    datas->on_mainloop = 0;
    destroy_dict(datas->texture_dict, NULL);
    free_storage_content(datas, 63);
}

int main(int ac, char **av)
{
    return (0);
}
