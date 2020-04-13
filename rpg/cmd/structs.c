/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** structs.h
*/

#include <entitylib.h>
#include <structs_1.h>

dict_t *define_structs(void)
{
    dict_t *structs = NULL;

    append_to_dict(&structs, "entity", define_entity(NULL));
    append_to_dict(&structs, "data", define_data_storage(NULL));
    append_to_dict(&structs, "meny", define_menu(NULL));
    return (structs);
}