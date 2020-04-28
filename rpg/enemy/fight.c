/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** fight.c
*/
#include <entitybase.h>
#include <capacity.h>
#include <data_storage.h>
#include <menu.h>
#include <event.h>
#include <enemy.h>
#include <fight.h>

void engage_fight(enemy_t *enemy, menu_t *menu)
{
    data_storage_t *datas = get_data_storage();
    fighting_t fight = {datas->player->sprite[(datas->player->size[2] << 1)
        - datas->player->frame_dec], datas->player, enemy, menu, 0, 1};

    sfRenderWindow_setView(menu->window, menu->view);
    sfSprite_setPosition(fight.player_sprite, (sfVector2f) {600, 250});
    draw_scene(&fight);
    sfRenderWindow_display(datas->window);
    sfSleep((sfTime) {30000});
    while (fight.player->hp > 0) {
        open_sub_menu(menu);
        ((capacity_t *) datas->global[ACTION])->effect(fight.player, enemy,
            ((capacity_t *) datas->global[ACTION])->animation, &fight);
        if (!fight.is_alive || enemy->hp <= 0)
            break;
        enemy_atk(&fight);
    }
    if (fight.player->hp <= 0)
        datas->is_alive = 0;
}

void engage_fight_event(event_t *self, player_t *player)
{
    dict_t *var = (dict_t *) get_executor()->var;

    (void) player;
    engage_fight(get_from_dict(get_from_dict(var, "local"),
        ((char *) self->tag) + 2), get_from_dict(get_from_dict(var, "menu"),
        ((char *) self->tag) + 26));
    get_data_storage()->key = (my_keys_t) {0, 0, 0, 0, 0};
}
