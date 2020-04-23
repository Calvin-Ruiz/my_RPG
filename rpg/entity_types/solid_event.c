/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** solid_event.c
*/

#include <entity.h>
#include <data_storage.h>
#include <solid_event.h>

void create_event_cmd(char **arr)
{
    event_t *event = malloc(sizeof(event_t));
    data_storage_t *datas = get_data_storage();
    char *name = arr[1];

    arr = create_entity_base((entity_t *) event, &datas->entities, arr);
    if (arr == NULL) {
        my_puterr("\e[91mFatal : Faild to build '");
        my_puterr(name);
        my_puterr("' event.\n\e[0m");
        return;
    }
    event->event = (void (*)(event_t *self, player_t *player)) arr[0];
    event->command_name = my_strdup(arr[1]);
    event->tag_id = -1;
    event->tag = NULL;
}

event_t *new_solid_event(char **arr)
{
    event_t *event = malloc(sizeof(event_t));

    if (*arr == NULL)
        return (NULL);
    *event = *(event_t *) *arr;
    event->pos.v1 = (sfVector2f) {(long) arr[1], (long) arr[2]};
    event->pos.v2 = (sfVector2f) {event->pos.v1.x + event->size[0],
        event->pos.v1.y + event->size[1]};
    return (event);
}

void default_event_update(event_t *self, int delta_time)
{
    self->timer += delta_time;
    if (self->timer >= self->frame_delay) {
        self->timer -= self->frame_delay;
        self->frame = (self->frame + 1) % self->size[2];
    }
}

void destroy_event(event_t *self)
{
    free(self);
}
