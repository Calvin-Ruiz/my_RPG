/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** menu.c
*/
#include <entitybase.h>
#include <data_storage.h>
#include <menu.h>

menu_t *create_menu(sfRenderWindow *window, sfTexture *background)
{
    menu_t *new = malloc(sizeof(menu_t));

    if (new == NULL)
        return (NULL);
    new->background = sfSprite_create();
    if (new->background && background)
        sfSprite_setTexture(new->background, background, sfTrue);
    new->window = window;
    new->view = sfView_copy(sfRenderWindow_getView(window));
    new->button = NULL;
    new->write_box = NULL;
    new->images = NULL;
    new->jauge = NULL;
    new->cursor = NULL;
    new->text = NULL;
    new->dtext = NULL;
    new->selected_write_box = NULL;
    return (new);
}

void menu_update(menu_t *menu, data_storage_t *datas)
{
    const sfVector2i real = sfMouse_getPositionRenderWindow(menu->window);
    const sfVector2u size = sfRenderWindow_getSize(menu->window);
    sfVector2f pos = sfView_getSize(menu->view);

    pos = (sfVector2f) {real.x * pos.x / size.x, real.y * pos.y / size.y};
    sfRenderWindow_setView(menu->window, menu->view);
    update_image_array(menu->window, menu->images);
    update_button_array(menu->window, menu->button, &datas->mouse, &pos);
    update_dynamic_text_array(menu->window, menu->dtext);
    update_text_array(menu->window, menu->text);
    sfRenderWindow_display(menu->window);
}

char menu_clic(menu_t *menu, sfMouseButtonEvent *mouse)
{
    const sfVector2u size = sfRenderWindow_getSize(menu->window);
    sfVector2f pos = sfView_getSize(menu->view);

    pos = (sfVector2f) {mouse->x * pos.x / size.x, mouse->y * pos.y / size.y};
    if (button_clic(menu, &pos))
        return (1);
    return (0);
}

void menu_events(menu_t *menu, data_storage_t *datas)
{
    sfEvent event;

    while (menu->opened && sfRenderWindow_pollEvent(menu->window, &event)) {
        if (event.type == sfEvtClosed) {
            my_closure(datas);
            return;
        }
        if (event.type == sfEvtMouseButtonReleased
            && event.mouseButton.button == sfMouseLeft) {
            datas->mouse.left = 0;
            menu_clic(menu, &event.mouseButton);
        }
        if (event.type == sfEvtMouseButtonPressed
            && event.mouseButton.button == sfMouseLeft)
            datas->mouse.left = 1;
    }
}

void open_menu(menu_t *menu)
{
    data_storage_t *datas = get_data_storage();

    menu->opened = 1;
    while (menu->opened) {
        sfRenderWindow_drawSprite(menu->window, menu->background, NULL);
        menu_update(menu, datas);
        menu_events(menu, datas);
    }
}
