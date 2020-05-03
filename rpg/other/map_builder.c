/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** map_builder.c
*/
#include <entitybase.h>
#include <data_storage.h>
#include <tools.h>
#include <fcntl.h>
#include <my_read.h>

char **get_map(void)
{
    static char *the_map = NULL;

    return (&the_map);
}

static void set_this_tile(data_storage_t *datas, sfMouseButtonEvent *event,
    u_char id, char *map)
{
    sfVector2i pos = {(int) (datas->pos.x - datas->size.x / 2 + event->x)
        >> datas->background->tile_size.x,
        (int) (datas->pos.y - datas->size.y / 2 + event->y)
        >> datas->background->tile_size.y};
    sfVertex *vertex = datas->background->vertex + 4 * (pos.x + pos.y *
        datas->background->map_size.x);
    const int y2 = 1 << datas->background->tile_size.y;
    const char x = datas->background->tile_size.x;

    map[pos.x + pos.y * (datas->background->map_size.x + 1)] = 'A' + id;
    (vertex++)->texCoords = (sfVector2f) {id << x, 0};
    (vertex++)->texCoords = (sfVector2f) {(id + 1) << x, 0};
    (vertex++)->texCoords = (sfVector2f) {(id + 1) << x, y2};
    (vertex++)->texCoords = (sfVector2f) {id << x, y2};
}

void mouse_edit(data_storage_t *datas, sfMouseButtonEvent *event, float delta)
{
    static char selected_tile = 0;
    static char *map = NULL;

    if (datas->debug == 0)
        return;
    if (map == NULL)
        map = *get_map();
    if (event) {
        set_this_tile(datas, event, selected_tile, map);
        return;
    }
    selected_tile -= delta;
    if (selected_tile >= (char) ((sfTexture_getSize(
        *datas->background->textures).x) >> datas->background->tile_size.x))
        selected_tile = 0;
    if (selected_tile < 0)
        selected_tile = (sfTexture_getSize(*datas->background->textures).x
            >> datas->background->tile_size.x) - 1;
}

void create_map(void)
{
    int fd = open(tmpcat(tmpcat("maps/", get_data_storage()->mapname), ".map"),
        O_RDONLY);
    long len = 0;

    *get_map() = my_read(fd, &len);
    close(fd);
}

void destroy_map(void)
{
    int fd = 0;
    data_storage_t *datas = get_data_storage();

    if (datas->debug) {
        fd = open(tmpcat(tmpcat("maps/", datas->mapname), ".map"), O_WRONLY);
        write(fd, *get_map(), (datas->background->map_size.x + 1) *
            datas->background->map_size.y);
        close(fd);
        free(*get_map());
    }
}
