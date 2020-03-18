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
    free_storage_content(datas, 7);
}

int main(int ac, char **av)
{
    return (0);
}
