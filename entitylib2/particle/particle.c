/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** particle.c
*/
#include <entitybase.h>
#include <data_storage.h>
#include <particle.h>
#include <string.h>

particle_list_t *create_particle_list(sfTexture *texture, u_short length)
{
    particle_list_t *plist = malloc(sizeof(particle_list_t));
    particle_t *particles = malloc(sizeof(particle_t) * length);
    vertex4_t *vertex = malloc(sizeof(vertex4_t) * length);

    if (plist == NULL || particles == NULL || vertex == NULL)
        return (NULL);
    memset(vertex, 0, sizeof(quad_t) * length);
    *plist = (particle_list_t) {(sfRenderStates) {sfBlendAlpha,
        sfTransform_Identity, texture, NULL}, (sfVertex *) vertex, particles,
        0, length};
    while (length-- > 0) {
        particles->attr.lifetime = 0;
        particles->attr.fading = 0;
        (particles++)->vertex = vertex++;
    }
    return (plist);
}

void update_particle_list(particle_list_t *plist, sfRenderWindow *window,
    sfVector2f *pos)
{
    particle_t *particle = plist->particles;
    u_short length = plist->length;

    while (length-- > 0)
        update_particle(particle++);
    plist->state.transform.matrix[2] = pos->x;
    plist->state.transform.matrix[5] = pos->y;
    sfRenderWindow_drawPrimitives(window, plist->vertex,
        plist->length << 2, sfQuads, (sfRenderStates *) plist);
}
