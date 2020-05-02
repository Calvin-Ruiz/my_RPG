/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** tile_manager.h
*/

#ifndef TILE_MANAGER_H_
#define TILE_MANAGER_H_

typedef struct tile_map {
    sfVertex *vertex;
    int nb_vertex;
    sfTexture **textures;
    char nb_textures;
    int delta_time;
    sfVector2u tile_size;
    sfVector2u map_size;
    sfRenderStates state;
} tile_map_t;

void load_tiles_from_file(tile_map_t *self, char *filename);
void build_tiles(tile_map_t *self);

static inline void draw_tile_map(sfRenderWindow *window, tile_map_t *self,
    long long actual)
{
    self->state.texture = self->textures[(actual / self->delta_time)
        % self->nb_textures];
    sfRenderWindow_drawPrimitives(window, self->vertex, self->nb_vertex,
        sfQuads, &self->state);
}

#endif /* TILE_MANAGER_H_ */
