/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** structs.c
*/

#include <entitylib.h>
#include <structs_1.h>

dict_t *define_structs(void)
{
    dict_t *structs = NULL;

    append_to_dict(&structs, "entity", define_entity(NULL));
    append_to_dict(&structs, "datas", define_data_storage(NULL));
    append_to_dict(&structs, "menu", define_menu(NULL));
    append_to_dict(&structs, "particle_param_t", define_particle_param(NULL));
    define_external_structs(&structs);
    return (structs);
}
