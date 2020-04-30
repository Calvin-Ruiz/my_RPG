/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** tile_manager.c
*/

#include <entitybase.h>
#include <data_storage.h>
#include <particle.h>
#include <my_read.h>
#include <tools.h>

void build_tiles(tile_map_t *self)
{
    register sfVector2f pos = {0, 0};
    register sfVector2u size = {1 << self->tile_size.x, 1 << self->tile_size.y};
    const vector2s_t max = {self->map_size.x, self->map_size.y};
    vertex4_t *vertex = malloc(sizeof(vertex4_t) * max.x * max.y);

    self->vertex = (sfVertex *) vertex;
    for (register short y = -1; ++y < max.y; pos.x = 0) {
        for (register short x = -1; ++x < max.x;) {
            vertex->p1.position = pos;
            vertex->p1.color = sfWhite;
            vertex->p4.position = (sfVector2f) {pos.x, pos.y + size.y};
            vertex->p4.color = sfWhite;
            pos.x += size.x;
            vertex->p2.position = pos;
            vertex->p2.color = sfWhite;
            vertex->p3.position = (sfVector2f) {pos.x, pos.y + size.y};
            (vertex++)->p3.color = sfWhite;
        }
        pos.y += size.y;
    }
}

void create_tile_map_cmd(char **arr)
{
    tile_map_t *new = my_malloc(sizeof(tile_map_t));

    new->state = (sfRenderStates) {sfBlendAlpha, sfTransform_Identity,
        (sfTexture *) arr[2], NULL};
    new->tile_size = (sfVector2u) {(long) arr[3], (long) arr[4]};
    new->map_size = (sfVector2u) {(long) arr[5], (long) arr[6]};
    new->nb_vertex = new->map_size.x * new->map_size.y * 4;
    build_tiles(new);
    *(tile_map_t **) arr[1] = new;
}

void load_tiles_from_file(tile_map_t *self, char *filename)
{
    vertex4_t *vertex = (vertex4_t *) self->vertex;
    const vector2s_t max = {self->map_size.x, self->map_size.y};
    const short tex_size = self->tile_size.x;
    const float tex_width = 1 << self->tile_size.x;
    const float tex_heigh = 1 << self->tile_size.y;
    int fd = open(filename, O_RDONLY);
    long len = 0;
    char *map = my_read(fd, &len);
    register float tex = 0;

    for (register short y = -1; ++y < max.y; map++) {
        for (register short x = -1; ++x < max.x;) {
            tex = ((short) ((*(map++)) - 'A')) << tex_size;
            vertex->p1.texCoords = (sfVector2f) {tex, 0};
            vertex->p2.texCoords = (sfVector2f) {tex + tex_width, 0};
            vertex->p3.texCoords = (sfVector2f) {tex + tex_width, tex_heigh};
            (vertex++)->p4.texCoords = (sfVector2f) {tex, tex_heigh};
        }
    }
    close(fd);
}

void load_tiles_from_file_cmd(char **arr)
{
    load_tiles_from_file(*(tile_map_t **) arr[1], arr[2]);
}
