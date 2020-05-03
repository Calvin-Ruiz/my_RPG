/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** choices.c
*/
#include <entitybase.h>
#include <data_storage.h>
#include <menu.h>
#include <executor.h>

void choice_yes(menu_t *menu)
{
    *(char *) get_from_rec_dict(get_from_rec_dict(get_executor()->var,
        "local"), "choice") = 1;
    menu->opened = 0;
}

void choice_no(menu_t *menu)
{
    *(char *) get_from_rec_dict(get_from_rec_dict(get_executor()->var,
        "local"), "choice") = 0;
    menu->opened = 0;
}

void update_capacities(void)
{
    execute_line("call level_up", get_executor());
}
