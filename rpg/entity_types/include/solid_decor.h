/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** solid_decor.h
*/

#ifndef SOLID_DECOR_H_
#define SOLID_DECOR_H_

typedef struct solid_decor {
    struct solid_decor *next;
    struct solid_decor *prev;
    struct solid_decor *disp_next;
    sfSprite **sprite;
    ushort_t *size;
    long long timer;
    long long frame_delay;
    uchar_t frame;
    uchar_t frame_dec;
    ushort_t id;
    int health;
    float speed;
    pos_t pos;
    void (*update)();
    void *(*new)();
    void (*destroy)();
    void *(*load)(struct solid_decor *self, int fd);
    void (*save)();
} decor_t;

void create_solid_decor_cmd(char **arr);
decor_t *new_solid_decor(char **arr);
void save_solid_decor(decor_t *self, int fd);
decor_t *load_solid_decor(decor_t *self, int fd);

#endif /* SOLID_DECOR_H_ */
