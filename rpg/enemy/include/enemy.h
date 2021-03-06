/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** enemy.h
*/

#ifndef ENEMY_H_
#define ENEMY_H_

typedef struct enemy {
    sfSprite *sprite;
    sfVector2f center;
    int hp;
    int max_hp;
    int atk;
    int def;
    int xp_drop;
    int money_drop;
    capacity_t *capacity;
    char nb_capacity;
} enemy_t;

#endif /* ENEMY_H_ */
