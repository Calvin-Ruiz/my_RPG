/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** capacity.c
*/

#include <entitybase.h>
#include <capacity.h>
#include <enemy.h>
#include <data_storage.h>
#include <menu.h>
#include <event.h>
#include <fight.h>

void create_capacity(char **arr)
{
    append_to_dict((dict_t **) arr[1], arr[2], arr[3]);
}

void create_sprite_anim(char **arr)
{
    *(sprite_anim_t *) arr[1] = (sprite_anim_t) {sfSprite_create(),
        (sfSound *) arr[3], (long) arr[4], (long) arr[5],
        (sfIntRect) {0, 0, (long) arr[6], (long) arr[7]}};
    if (((sprite_anim_t *) arr[1])->sprite == NULL || arr[2] == NULL) {
        my_puterr("\e[31mCreateError : Failed to create animation\n\e[0m");
        return;
    }
    sfSprite_setOrigin(((sprite_anim_t *) arr[1])->sprite,
        (sfVector2f) {(long) arr[6] >> 1, (long) arr[7] >> 1});
    sfSprite_setTexture(((sprite_anim_t *) arr[1])->sprite,
        (sfTexture *) arr[2], sfTrue);
}

void player_atk_sprite(player_t *player, enemy_t *enemy,
    sprite_anim_t *animation, fighting_t *fight)
{
    sfIntRect rect = animation->scale;
    sfRenderWindow *window = fight->menu->window;

    enemy->hp -= player->atk * 1.5 - enemy->def;
    if (animation->sound)
        sfSound_play(animation->sound);
    sfSprite_setPosition(animation->sprite, enemy->center);
    for (short frame = -1; ++frame < animation->nb_frames;) {
        sfSprite_setTextureRect(animation->sprite, rect);
        rect.left += rect.width;
        for (char n = animation->frame_duration; n-- > 0;) {
            sfSprite_setColor(fight->enemy.sprite, (sfColor) {255,
                255 - 255 * (n + frame * animation->frame_duration) /
                (animation->frame_duration * animation->nb_frames),
                255 - 255 * (n + frame * animation->frame_duration) /
                (animation->frame_duration * animation->nb_frames), 255});
            draw_scene(fight);
            sfRenderWindow_drawSprite(window, animation->sprite, NULL);
            sfRenderWindow_display(window);
            sfSleep((sfTime) {25000});
        }
    }
}

void enemy_atk_sprite(enemy_t *enemy, player_t *player,
    sprite_anim_t *animation, fighting_t *fight)
{
    sfIntRect rect = animation->scale;
    sfRenderWindow *window = fight->menu->window;

    player->hp -= enemy->atk * 1.5 - player->def;
    if (animation->sound)
        sfSound_play(animation->sound);
    sfSprite_setPosition(animation->sprite,
        (sfVector2f) {500 + player->size[0] / 2, 250 + player->size[1] / 2});
    for (short frame = animation->nb_frames; frame-- > 0;) {
        sfSprite_setTextureRect(animation->sprite, rect);
        rect.left += rect.width;
        for (char n = animation->frame_duration; n-- > 0;) {
            sfSprite_setColor(fight->player_sprite, (sfColor) {255,
                255 - 255 * (n + frame * animation->frame_duration) /
                (animation->frame_duration * animation->nb_frames),
                255 - 255 * (n + frame * animation->frame_duration) /
                (animation->frame_duration * animation->nb_frames), 255});
            draw_scene(fight);
            sfRenderWindow_drawSprite(window, animation->sprite, NULL);
            sfRenderWindow_display(window);
            sfSleep((sfTime) {25000});
        }
    }
}

void give_capacity_cmd(char **arr)
{
    char i = (long) arr[-1] - 2;
    player_t *player = (player_t *) arr[1];
    capacity_t *capacity = NULL;

    while (i-- > 0) {
        capacity = malloc(sizeof(capacity_t));
        if (capacity == NULL)
            continue;
        *capacity = **(capacity_t **) (++arr);
        capacity->next = player->capacity;
        player->capacity = capacity;
    }
}
