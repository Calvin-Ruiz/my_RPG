/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** particle.h
*/

#ifndef PARTICLE_H_
#define PARTICLE_H_

typedef struct quad_vertex {
    sfVertex p1;
    sfVertex p2;
    sfVertex p3;
    sfVertex p4;
} vertex4_t;

typedef struct particle_attributes {
    sfVector2f velocity;
    sfVector2f force;
    float acceleration;
    struct {
        char r;
        char g;
        char b;
        char a;
    } coloring;
    u_short lifetime;
    u_short fading;
} particle_attr_t;

typedef struct particle_properties {
    particle_attr_t attr;
    pos_t pos;
    pos_t rect;
    sfColor color;
} particle_param_t;

typedef struct particle {
    vertex4_t *vertex;
    particle_attr_t attr;
} particle_t;

typedef struct particle_list {
    sfRenderStates state;
    sfVertex *vertex;
    particle_t *particles;
    u_short last;
    u_short length;
} particle_list_t;

typedef struct emitter {
    char is_active;
    short min_particle;
    short variation;
    short spawn_waiting;
    char spawn_holding;
    short waiting;
    char holding;
    sfIntRect area;
    particle_list_t *target;
    particle_param_t *particle;
    pos_t *rect;
    char nb_rect;
} emitter_t;

static inline void append_particle(particle_list_t *plist,
    particle_param_t *params)
{
    particle_t *self = plist->particles + (plist->last++);

    if (plist->last == plist->length)
        plist->last = 0;
    self->attr = params->attr;
    self->vertex->p1.color = params->color;
    self->vertex->p1.position = params->pos.v1;
    self->vertex->p3.position = params->pos.v2;
    self->vertex->p1.texCoords = params->rect.v1;
    self->vertex->p2.texCoords = (sfVector2f) {params->rect.v2.x,
        params->rect.v1.y};
    self->vertex->p3.texCoords = params->rect.v2;
    self->vertex->p4.texCoords = (sfVector2f) {params->rect.v1.x,
        params->rect.v2.y};
}

static inline void update_particle_movement(particle_t *particle)
{
    vertex4_t *v = particle->vertex;

    if (particle->attr.lifetime) {
        particle->attr.velocity.x = (particle->attr.velocity.x +
            particle->attr.force.x) * particle->attr.acceleration;
        particle->attr.velocity.y = (particle->attr.velocity.y +
            particle->attr.force.y) * particle->attr.acceleration;
    } else {
        particle->attr.velocity.x *= particle->attr.acceleration;
        particle->attr.velocity.y *= particle->attr.acceleration;
    }
    v->p1.position.x += particle->attr.velocity.x;
    v->p1.position.y += particle->attr.velocity.y;
    v->p3.position.x += particle->attr.velocity.x;
    v->p3.position.y += particle->attr.velocity.y;
    v->p2.position = (sfVector2f) {v->p3.position.x, v->p1.position.y};
    v->p4.position = (sfVector2f) {v->p1.position.x, v->p3.position.y};
}

static inline void update_particle(particle_t *particle)
{
    sfColor color = particle->vertex->p1.color;

    if (particle->attr.fading == 0)
        return;
    color.r += particle->attr.coloring.r;
    color.g += particle->attr.coloring.g;
    color.b += particle->attr.coloring.b;
    color.a += particle->attr.coloring.a;
    if (particle->attr.lifetime == 0) {
        color.a -= color.a / particle->attr.fading--;
    } else
        particle->attr.lifetime--;
    particle->vertex->p1.color = color;
    particle->vertex->p2.color = color;
    particle->vertex->p3.color = color;
    particle->vertex->p4.color = color;
    update_particle_movement(particle);
}

particle_list_t *create_particle_list(sfTexture *texture, u_short length);
void update_particle_list(particle_list_t *plist, sfRenderWindow *window,
    sfVector2f *pos);
void append_particle_cmd(char **arr);
void create_particle_emitter_cmd(char **arr);
void update_all_particle_emitter(dict_t *emitters);

#endif /* PARTICLE_H_ */
