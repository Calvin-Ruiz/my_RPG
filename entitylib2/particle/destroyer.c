/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** destroyer.c
*/
#include <entitybase.h>
#include <data_storage.h>
#include <particle.h>

void destroy_particle_list(particle_list_t *plist)
{
    free(plist->particles);
    free(plist->vertex);
    free(plist);
}
