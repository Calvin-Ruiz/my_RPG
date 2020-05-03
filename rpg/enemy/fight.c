/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** fight.c
*/
#include <entitybase.h>
#include <capacity.h>
#include <data_storage.h>
#include <internal_data.h>
#include <menu.h>
#include <event.h>
#include <enemy.h>
#include <item_list.h>
#include <fight.h>
#include <pause.h>

static void init_fight(fighting_t *fight, menu_t *menu)
{
    menu->dtext->data = &fight->enemy.hp;
    sfRenderWindow_setView(menu->window, menu->view);
    sfSprite_setPosition(fight->player_sprite, (sfVector2f) {500, 250});
    draw_scene(fight);
    sfRenderWindow_display(menu->window);
    sfSleep((sfTime) {30000});
}

static void uninit_fight(fighting_t *fight, data_storage_t *datas)
{
    if (fight->player->hp <= 0) {
        datas->is_alive = 0;
        datas->on_mainloop = 0;
        ((menu_t *) datas->main_menu)->opened = 0;
    } else {
        give_xp(datas->player, fight->enemy.money_drop);
        datas->player->money += fight->enemy.money_drop;
    }
    reset_timers(datas, NULL);
}

void engage_fight(enemy_t *enemy, menu_t *menu)
{
    data_storage_t *datas = get_data_storage();
    fighting_t fight = {datas->player->sprite[(datas->player->size[2] << 1)
        - datas->player->frame_dec], datas->player, *enemy, menu, 0, 1};

    datas->global[ENEMY] = &fight.enemy;
    init_fight(&fight, menu);
    while (fight.player->hp > 0) {
        open_sub_menu(menu);
        ((capacity_t *) datas->global[ACTION])->effect(fight.player,
            &fight.enemy, ((capacity_t *) datas->global[ACTION])->animation,
            &fight);
        if (!fight.is_alive || fight.enemy.hp <= 0)
            break;
        enemy_atk(&fight);
    }
    uninit_fight(&fight, datas);
}

void engage_fight_event(event_t *self, player_t *player)
{
    dict_t *var = (dict_t *) get_executor()->var;
    menu_t *menu = get_from_dict(get_from_dict(var, "menu"),
        ((char *) self->tag) + 26);
    data_storage_t *datas = get_data_storage();

    datas->key = (my_keys_t) {0, 0, 0, 0, 0};
    datas->global[ACTION] = player->capacity;
    engage_fight(get_from_dict(get_from_dict(var, "local"),
        ((char *) self->tag) + 2), menu);
    destroy_button_array(menu->dlist->local);
    menu->dlist->local = NULL;
    calculate_final_characteristics(player);
    self->health = 0;
    call_function(((char **) &(caller_t) {4, call_function,
        self->command_name, self, player}) + 1);
}

char on_clic_fight_item(dynamic_list_t *self, sfVector2f *pos)
{
    item_list_t *ilist = self->local;
    data_storage_t *data;

    while (ilist) {
        if (ilist->button->pos.v1.x <= pos->x
            && ilist->button->pos.v2.x > pos->x
            && ilist->button->pos.v1.y <= pos->y
            && ilist->button->pos.v2.y > pos->y) {
            data = get_data_storage();
            consume_item_from_fight(ilist->button->data,
                ((capacity_t *) data->global[ACTION])->effect ==
                (void (*)(void *, void *, void *, void *)) use_item_for_me ?
                data->player : data->global[ENEMY]);
            return (1);
        }
        ilist = ilist->next;
    }
    return (0);
}
