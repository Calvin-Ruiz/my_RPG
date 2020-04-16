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
#include <tools.h>

particle_list_t *create_particle_list(sfTexture *texture, u_short length)
{
    particle_list_t *plist = malloc(sizeof(particle_list_t));
    particle_t *particles = malloc(sizeof(particle_t) * length);
    vertex4_t *vertex = malloc(sizeof(vertex4_t) * length);

    if (plist == NULL || particles == NULL || vertex == NULL)
        return (NULL);
    memset(vertex, 0, sizeof(vertex4_t) * length);
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
    if (pos) {
        plist->state.transform.matrix[2] = pos->x;
        plist->state.transform.matrix[5] = pos->y;
    }
    sfRenderWindow_drawPrimitives(window, plist->vertex,
        plist->length << 2, sfQuads, (sfRenderStates *) plist);
}

void update_particle_emitter(particle_list_t *plist, emitter_t *emitter)
{
    short nb_spawn;
    particle_param_t *param = emitter->particle;

    if (emitter->waiting-- > 0)
        return;
    if (emitter->waiting == 0)
        emitter->holding = emitter->spawn_holding;
    if (emitter->holding-- <= 0)
        emitter->waiting = emitter->spawn_waiting;
    nb_spawn = emitter->min_particle + rand() % emitter->variation;
    for (short i = -1; ++i < nb_spawn;) {
        param->rect = emitter->rect[rand() % emitter->nb_rect];
        param->pos.v1.x = emitter->area.left + rand() % emitter->area.width;
        param->pos.v1.y = emitter->area.top + rand() % emitter->area.height;
        param->pos.v2.x = param->pos.v1.x + param->rect.v2.x - param->rect.v1.x;
        param->pos.v2.y = param->pos.v1.y + param->rect.v2.y - param->rect.v1.y;
        append_particle(plist, param);
    }
}

void create_particle_emitter_cmd(char **arr)
{
    dict_t **emitter_dict = &get_data_storage()->particle_emitters;
    emitter_t *emitter = my_malloc(sizeof(emitter_t));
    char *name = arr[1];
    pos_t *rect;

    *emitter = (emitter_t) {(long) arr[2], (long) arr[3], (long) arr[4],
        (long) arr[5], 0, 0, (sfIntRect) {(long) arr[6], (long) arr[7],
        (long) arr[8], (long) arr[9]}, (particle_param_t *) arr[10],
        my_malloc((long) arr[11] * sizeof(pos_t)), (long) arr[11]};
    arr += 12;
    rect = emitter->rect;
    for (u_char i = (long) arr[-1]; i-- > 0; arr += 4) {
        *(rect++) = (pos_t) {(sfVector2f) {(long) arr[0], (long) arr[1]},
            (sfVector2f) {(long) arr[2], (long) arr[3]}};
    }
    append_to_dict(emitter_dict, name, emitter);
}
