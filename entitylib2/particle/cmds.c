/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** cmds.c
*/
#include <entitybase.h>
#include <tools.h>
#include <dict.h>
#include <particle.h>

void append_particle_cmd(char **arr)
{
    append_particle((particle_list_t *) arr[1], (particle_param_t *) arr[2]);
}
