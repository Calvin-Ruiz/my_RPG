/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** main.c
*/
#include <main.h>
#include <pause.h>
#include <events.h>
#include <entity_display.h>
#include <etools.h>
#include <decor.h>
#include <event.h>
#include <npc.h>
#include <data_io.h>
#include <player_io.h>
#include <tile_manager.h>
#include <cmd_uninit.h>

void my_closure(data_storage_t *datas)
{
    sfRenderWindow_close(datas->window);
    datas->on_mainloop = 0;
    ((menu_t *) datas->main_menu)->opened = 0;
    ((menu_t *) datas->pause_menu)->opened = 0;
    datas->is_alive = 0;
}

void my_event(data_storage_t *datas, long long *last)
{
    sfEvent event;

    while (datas->on_mainloop &&
        sfRenderWindow_pollEvent(datas->window, &event)) {
        if (event.type == sfEvtClosed) {
            my_closure(datas);
            return;
        }
        if (event.type == sfEvtKeyPressed)
            event_press(datas, event.key.code, last);
        if (event.type == sfEvtKeyReleased)
            event_release(datas, event.key.code);
        if (event.type == sfEvtMouseButtonPressed)
            mouse_clic(datas, &event.mouseButton);
        if (event.type == sfEvtMouseButtonReleased)
            mouse_release(datas, &event.mouseButton);
        if (event.type == sfEvtMouseWheelScrolled)
            event_scroll(datas, event.mouseWheelScroll.delta);
    }
}

void mainloop(data_storage_t *datas, sfRenderWindow *window)
{
    long long last = sfClock_getElapsedTime(datas->clock).microseconds;
    long long actual = last;

    while (datas->on_mainloop) {
        srand(actual);
        draw_tile_map(window, datas->background);
        update_player_attributes(datas);
        decor_update(datas->entitylists[DECOR_LIST], datas->player);
        event_update(datas->entitylists[EVENT_LIST], datas->player);
        display_entities(window, &(*datas->entitylists)->next);
        npc_update(datas->entitylists[NPC_LIST], datas->player);
        update_all_particle_emitter(datas->particle_emitters);
        update_particle_list(datas->particle_lists->data, window, NULL);
        update_window(window, datas);
        actual = sfClock_getElapsedTime(datas->clock).microseconds;
        last = actual < last + 1000000 ? last + 25000 : actual + 25000;
        if (actual < last)
            sfSleep((sfTime) {last - actual});
        my_event(datas, &last);
    }
}

static void init_game(data_storage_t *datas)
{
    get_internal_data()->text_font = sfFont_createFromFile("text_font.ttf");
    init_some_datas(datas);
    init_pause_buttons(datas->pause_menu);
    append_to_dict(&datas->particle_lists, "fight", create_particle_list(
        get_from_dict(datas->textures, "particle"), 3000));
    append_to_dict(&datas->particle_lists, "main", create_particle_list(
        get_from_dict(datas->textures, "particle"), 3000));
    init_executor();
    load_tags(datas->path);
    load_player(datas->player, datas);
    load_tiles_from_file(datas->background, datas->mapname);
    load_entities(datas->path, datas->mapname);
    sfRenderWindow_setFramerateLimit(datas->window, datas->fps);
}

int main(void)
{
    data_storage_t *datas = init_data_storage(NB_ENTITYLIST);

    if (init_textures(datas) || init_sounds(datas) ||
        create_window((sfVideoMode) {800, 600, 32}, "My RPG",
        sfResize | sfClose, 60))
        return (84);
    init_game(datas);
    open_menu(datas->main_menu);
    clear_trace(NULL);
    if (datas->player->hp > 0) {
        save_entities(datas->path, datas->mapname);
        save_tags(datas->path);
        save_player(datas->player, datas);
    }
    free_storage_content(datas, 7);
    cmd_uninit();
    return (0);
}
