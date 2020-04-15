/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** data_storage.h
*/

#ifndef DATA_STORAGE_H_
#define DATA_STORAGE_H_

#include <dict.h>
#include <player.h>

enum {
    ITEMS,
    CAPACITY,
    EFFECTS,
    NB_DATAS,
};

typedef struct saved_datas {
    struct saved_datas *next;
    void *data;
    ushort_t id;
} saved_t;

typedef struct my_mouse {
    char left;
    char wheel;
    char right;
    sfVector2f pos;
} my_mouse_t;

typedef struct my_keys {
    char left;
    char right;
    char up;
    char down;
    char space;
} my_keys_t;

typedef struct data_storage {
    sfRenderWindow *window;
    sfView *view;
    sfVector2f pos;
    sfVector2f size;
    char *path;
    char *mapname;
    saved_t *saved;
    void *main_menu;
    void *pause_menu;
    void *global[NB_DATAS];
    my_mouse_t mouse;
    my_keys_t key;
    dict_t *sound_buffs;
    dict_t *sounds;
    dict_t *textures;
    dict_t *entities;
    dict_t *particle_lists;
    player_t *player;
    entitylist_t **entitylists;
    int nb_entitylist;
    int score;
    int higher_score;
    float coef_x;
    float coef_y;
    sfClock *clock;
    int fps;
    sfMusic *music;
    float volume;
    char on_mainloop;
    char is_alive;
    char ask_command;
} data_storage_t;

data_storage_t *get_data_storage(void);
data_storage_t *init_data_storage(int nb_entitylist);
int check_data_storage_content(data_storage_t *datas);
void free_storage_content(data_storage_t *datas, int mask);
void update_all(data_storage_t *datas);
void import_sound(data_storage_t *datas, char *filename);
void save_higher_score(data_storage_t *datas);
short append_saved(data_storage_t *datas, void *data);

static inline void **get_tag_from_id(saved_t *saved, short id)
{
    while (saved) {
        if (saved->id == id)
            return (&saved->data);
        saved = saved->next;
    }
    return (NULL);
}

#endif /* DATA_STORAGE_H_ */
