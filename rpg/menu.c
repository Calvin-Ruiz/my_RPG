/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** menu.c
*/
#include <main.h>
#include <fcntl.h>
#include <pause.h>
#include <htp.h>

void start_mainloop(data_storage_t *datas)
{
    datas->on_mainloop = 1;
    reset_timers(datas, NULL);
    mainloop(datas, datas->window);
}

void init_some_datas(data_storage_t *datas)
{
    sfTexture *btn_back = get_from_dict(datas->textures, "button");
    sfTexture *background = get_from_dict(datas->textures, "menu");
    menu_t *main_menu = create_menu(datas->window, background);
    sfFont *font = get_internal_data()->text_font;
    datas->pause_menu = create_menu(datas->window, background);
    datas->main_menu = main_menu;
    main_menu->button = create_button(btn_back, font, (pos_t) {(sfVector2f)
        {272, 200}, (sfVector2f) {256, 64}}, (void (*)(void *)) start_mainloop);
    main_menu->button->next = create_button(btn_back, font, (pos_t)
        {(sfVector2f) {272, 500}, (sfVector2f) {256, 64}},
        (void (*)(void *)) my_closure);
    main_menu->button->data = get_data_storage();
    main_menu->button->next->data = get_data_storage();
    main_menu->button->next->next = NULL;
    sfText_setString(main_menu->button->text, "Play");
    sfText_setString(main_menu->button->next->text, "Quit");
    datas->view = sfView_copy(sfRenderWindow_getView(datas->window));
    datas->pos = sfView_getCenter(datas->view);
    datas->size = sfView_getSize(datas->view);
    init_htp_button(datas);
}
