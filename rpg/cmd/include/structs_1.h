/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** structs_1.h
*/

#ifndef STRUCTS_1_H_
#define STRUCTS_1_H_

#include <menu.h>
#include <particle.h>

static inline dict_t *define_entity(entity_t * const ref)
{
    dict_t *new = NULL;
    append_to_dict(&new, "next", &ref->next);
    append_to_dict(&new, "prev", &ref->prev);
    append_to_dict(&new, "disp_next", &ref->disp_next);
    append_to_dict(&new, "sprite", &ref->sprite);
    append_to_dict(&new, "size", &ref->size);
    append_to_dict(&new, "timer", &ref->timer);
    append_to_dict(&new, "frame_delay", &ref->frame_delay);
    append_to_dict(&new, "frame_dec", &ref->frame_dec);
    append_to_dict(&new, "frame", &ref->frame);
    append_to_dict(&new, "id", &ref->id);
    append_to_dict(&new, "health", &ref->health);
    append_to_dict(&new, "speed", &ref->speed);
    append_to_dict(&new, "pos_x1", &ref->pos.v1.x);
    append_to_dict(&new, "pos_y1", &ref->pos.v1.y);
    append_to_dict(&new, "pos_x2", &ref->pos.v2.x);
    append_to_dict(&new, "pos_y2", &ref->pos.v2.y);
    append_to_dict(&new, "update", &ref->update);
    append_to_dict(&new, "new", &ref->new);
    return (new);
}

static inline dict_t *define_data_storage(data_storage_t * const ref)
{
    dict_t *new = NULL;

    append_to_dict(&new, "window", &ref->window);
    append_to_dict(&new, "view", &ref->view);
    append_to_dict(&new, "pos", &ref->pos);
    append_to_dict(&new, "size", &ref->size);
    append_to_dict(&new, "path", &ref->path);
    append_to_dict(&new, "mapname", &ref->mapname);
    append_to_dict(&new, "saved", &ref->saved);
    append_to_dict(&new, "nb_entitylist", &ref->nb_entitylist);
    append_to_dict(&new, "coef_x", &ref->coef_x);
    append_to_dict(&new, "coef_y", &ref->coef_y);
    append_to_dict(&new, "clock", &ref->clock);
    append_to_dict(&new, "fps", &ref->fps);
    append_to_dict(&new, "music", &ref->music);
    append_to_dict(&new, "volume", &ref->volume);
    append_to_dict(&new, "on_mainloop", &ref->on_mainloop);
    append_to_dict(&new, "is_alive", &ref->is_alive);
    append_to_dict(&new, "ask_command", &ref->ask_command);
    return (new);
}

static inline dict_t *define_menu(menu_t * const ref)
{
    dict_t *new = NULL;

    append_to_dict(&new, "window", &ref->window);
    append_to_dict(&new, "view", &ref->view);
    append_to_dict(&new, "background", &ref->background);
    append_to_dict(&new, "button", &ref->button);
    append_to_dict(&new, "write_box", &ref->write_box);
    append_to_dict(&new, "images", &ref->images);
    append_to_dict(&new, "jauge", &ref->jauge);
    append_to_dict(&new, "cursor", &ref->cursor);
    append_to_dict(&new, "text", &ref->text);
    append_to_dict(&new, "dtext", &ref->dtext);
    append_to_dict(&new, "selected_write_box", &ref->selected_write_box);
    append_to_dict(&new, "opened", &ref->opened);
    return (new);
}

static inline dict_t *define_particle_param(particle_param_t * const ref)
{
    dict_t *new = NULL;

    append_to_dict(&new, "vel_x", &ref->attr.velocity.x);
    append_to_dict(&new, "vel_y", &ref->attr.velocity.y);
    append_to_dict(&new, "force_x", &ref->attr.force.x);
    append_to_dict(&new, "force_y", &ref->attr.force.y);
    append_to_dict(&new, "acceleration", &ref->attr.acceleration);
    append_to_dict(&new, "coloring", &ref->attr.coloring);
    append_to_dict(&new, "lifetime", &ref->attr.lifetime);
    append_to_dict(&new, "fading", &ref->attr.fading);
    append_to_dict(&new, "x1", &ref->pos.v1.x);
    append_to_dict(&new, "y1", &ref->pos.v1.y);
    append_to_dict(&new, "x2", &ref->pos.v2.x);
    append_to_dict(&new, "y2", &ref->pos.v2.y);
    append_to_dict(&new, "color", &ref->color);
    return (new);
}

#endif /* STRUCTS_1_H_ */
