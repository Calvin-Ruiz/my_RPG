/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** data_storage.h
*/

#ifndef DATA_STORAGE_H_
#define DATA_STORAGE_H_

#include <dict.h>

enum {
    NB_DATAS,
};

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
    void *main_menu;
    void *pause_menu;
    void *global[NB_DATAS];
    my_mouse_t mouse;
    my_keys_t key;
    dict_t *sound_buffs;
    dict_t *sounds;
    dict_t *textures;
    dict_t *entities;
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
} data_storage_t;

data_storage_t *get_data_storage(void);
data_storage_t *init_data_storage(int nb_entitylist);
int check_data_storage_content(data_storage_t *datas);
void free_storage_content(data_storage_t *datas, int mask);
void update_all(data_storage_t *datas);
void import_sound(data_storage_t *datas, char *filename);
void save_higher_score(data_storage_t *datas);

#endif /* DATA_STORAGE_H_ */
