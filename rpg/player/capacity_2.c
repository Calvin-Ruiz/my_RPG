/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** capacity_2.c
*/

#include <entitybase.h>
#include <capacity.h>
#include <enemy.h>
#include <data_storage.h>
#include <menu.h>
#include <event.h>
#include <fight.h>

void use_item_for_me(enemy_t *enemy, player_t *player,
    sprite_anim_t *animation, fighting_t *fight)
{
    (void) player;
    (void) enemy;
    
    if (animation->sound)
        sfSound_play(animation->sound);
    for (u_char i = -1; ++i < 11;) {
        sfSprite_setColor(fight->player_sprite,
            (sfColor) {(255 * i) / 10, 255, (255 * i) / 10, 255});
        draw_scene(fight);
        sfSleep((sfTime) {25000});
    }
}

void use_item_for_you(enemy_t *enemy, player_t *player,
    sprite_anim_t *animation, fighting_t *fight)
{
    (void) player;
    if (animation->sound)
        sfSound_play(animation->sound);
    for (u_char i = -1; ++i < 11;) {
        sfSprite_setColor(enemy->sprite,
            (sfColor) {255, (255 * i) / 10, 127 + (128 * i) / 10, 255});
        draw_scene(fight);
        sfSleep((sfTime) {25000});
    }
}
