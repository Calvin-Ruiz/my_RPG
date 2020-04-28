/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** capacity.h
*/

#ifndef CAPACITY_H_
#define CAPACITY_H_

enum {
    HIMSELF,
    ENNEMY,
};

typedef struct capacity {
    struct capacity *next;
    short id;
    char target;
    void *animation;
    void (*effect)(void *user, void *target, void *animation, void *fight);
} capacity_t;

typedef struct animation_sprites {
    sfSprite *sprite;
    sfSound *sound;
    short nb_frames;
    char frame_duration;
    sfIntRect scale;
} sprite_anim_t;

#endif /* CAPACITY_H_ */
