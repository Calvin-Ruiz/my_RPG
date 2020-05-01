/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** window_manager.c
*/
#include <entitybase.h>
#include <internal_data.h>
#include <data_storage.h>

static int create_backgrounds(internal_data_t *datas)
{
    datas->background = sfSprite_create();
    if (datas->background_skin == NULL || datas->background == NULL)
        return (84);
    sfSprite_setTexture(datas->background, datas->background_skin, sfTrue);
    return (0);
}

static int create_window_2(internal_data_t *datas, data_storage_t *stor)
{
    datas->icon = sfImage_createFromFile("textures/icon.png");
    if (datas->icon == NULL)
        return (84);
    sfVector2u size = sfImage_getSize(datas->icon);
    const sfUint8 *icon = sfImage_getPixelsPtr(datas->icon);
    sfRenderWindow_setIcon(stor->window, size.x, size.y, icon);
    datas->background_skin = sfTexture_createFromFile("textures/background.png",
        NULL);
    datas->fullscreen = 0;
    if (create_backgrounds(datas))
        return (84);
    return (0);
}

int create_window(sfVideoMode mode, char *name, long int args, int fps)
{
    data_storage_t *stor = get_data_storage();
    internal_data_t *datas = get_internal_data();
    stor->fps = fps;
    stor->window = sfRenderWindow_create(mode, name, args, NULL);
    if (!stor->window)
        return (84);
    stor->view = sfView_copy(sfRenderWindow_getView(stor->window));
    sfRenderWindow_setFramerateLimit(stor->window, fps);
    sfRenderWindow_setView(stor->window, stor->view);
    sfSprite_setTexture(datas->cursor, datas->cursor_skin, sfTrue);
    return (create_window_2(datas, stor));
}

void destroy_window(data_storage_t *stor)
{
    internal_data_t *datas = get_internal_data();

    sfView_destroy(stor->view);
    sfTexture_destroy(datas->cursor_skin);
    sfTexture_destroy(datas->background_skin);
    sfSprite_destroy(datas->cursor);
    sfSprite_destroy(datas->background);
    sfImage_destroy(datas->icon);
    sfRenderWindow_destroy(stor->window);
}

void update_window(sfRenderWindow *window, data_storage_t *stor)
{
    sfVector2u size = sfRenderWindow_getSize(window);

    if (size.x < 800 || size.x > 1920)
        size.x = (size.x < 800) ? 800 : 1920;
    if (size.y < 600 || size.y > 1080)
        size.y = (size.y < 600) ? 600 : 1080;
    sfRenderWindow_setSize(window, size);
    stor->coef_x = stor->size.x / size.x;
    stor->coef_y = stor->size.y / size.y;
    sfRenderWindow_display(window);
}
