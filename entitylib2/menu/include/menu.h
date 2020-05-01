/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** menu.h
*/

#ifndef MENU_H_
#define MENU_H_

typedef struct btn {
    struct btn *next;
    sfSprite *display[3];
    sfText *text;
    pos_t pos;
    void *data;
    void (*press_action)(void *data);
} button_t;

button_t *create_button(sfTexture *texture, sfFont *font, pos_t *pos,
    void (*press_action)(void *data));
void update_button_array(sfRenderWindow *window, button_t *button,
    my_mouse_t *mouse, sfVector2f *pos);
void destroy_button_array(button_t *button);

typedef struct wbx {
    struct write_box *next;
    sfSprite *background;
    sfText *text;
    char *str;
    void (*on_return)(struct wbx *self);
    pos_t pos;
} write_box_t;

typedef struct imagez {
    struct imagez *next;
    sfSprite *image;
} image_t;

image_t *create_image(sfTexture *texture, pos_t *pos);
void create_image_cmd(char **arr);
void update_image_array(sfRenderWindow *window, image_t *image);
void destroy_image_array(image_t *image);

typedef struct jge {
    struct jge *next;
    sfRectangleShape *back;
    sfRectangleShape *fore;
    void *data;
    void (*update)(struct jge *self);
} jauge_t;

typedef struct crsr {
    struct crsr *next;
    int min;
    int max;
    int actual;
    sfVector2f pos;
    sfSprite *background;
    sfSprite *cursor;
    void *data;
    void (*on_hold)(struct crsr *self, sfVector2f relative_pos);
} cursor_t;

typedef struct dtx {
    struct dtx *next;
    sfText *text;
    sfVector2f pos;
    void *data;
    void *last;
    void (*update)(struct dtx *self);
} dynamic_text_t;

void create_dynamic_text_cmd(char **arr);
void update_dynamic_text_from_2int(dynamic_text_t *self);
void update_dynamic_text_from_int(dynamic_text_t *self);
void update_dynamic_text_array(sfRenderWindow *window, dynamic_text_t *dtext);
void destroy_dynamic_text_array(dynamic_text_t *dynamic_text);

typedef struct tx {
    struct tx *next;
    sfText *text;
    sfVector2f pos;
} text_t;

void create_text_cmd(char **arr);
void update_text_array(sfRenderWindow *window, text_t *text);
void destroy_text_array(text_t *text);

typedef struct dlist {
    struct dlist *next;
    sfSprite *background;
    pos_t pos;
    void *local;
    void *data;
    void (*update)(struct dlist *self, sfRenderWindow *window,
        data_storage_t *datas, sfVector2f *mouse);
    char (*on_clic)(struct dlist *self, sfVector2f *pos);
} dynamic_list_t;

void create_dynamic_list_cmd(char **arr);

typedef struct {
    sfRenderWindow *window;
    sfView *view;
    sfSprite *background;
    button_t *button;
    write_box_t *write_box;
    image_t *images;
    jauge_t *jauge;
    cursor_t *cursor;
    text_t *text;
    dynamic_text_t *dtext;
    write_box_t *selected_write_box;
    dynamic_list_t *dlist;
    char opened;
} menu_t;

char button_clic(button_t *button, sfVector2f *pos);
char dynamic_list_clic(menu_t *menu, sfVector2f *pos);
menu_t *create_menu(sfRenderWindow *window, sfTexture *background);
void menu_update(menu_t *menu, data_storage_t *datas);
char menu_clic(menu_t *menu, sfMouseButtonEvent *mouse);
void open_menu(menu_t *menu);
void my_closure(data_storage_t *datas);
void open_sub_menu(menu_t *menu);
void menu_events(menu_t *menu, data_storage_t *datas);
void destroy_menu(menu_t *menu);

#endif /* MENU_H_ */
