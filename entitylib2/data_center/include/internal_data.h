/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** internal_data.h
*/

#ifndef INTERNAL_DATA_H_
#define INTERNAL_DATA_H_

typedef struct internal_data {
    int fullscreen;
    sfTexture *cursor_skin;
    sfTexture *background_skin;
    sfTexture *level_completed_skin;
    sfImage *icon;
    sfSprite *game_over;
    sfSprite *cursor;
    sfSprite *background;
    sfSprite *level_completed;
    sfFont *text_font;
    sfText *score_text;
} internal_data_t;

internal_data_t *get_internal_data(void);

#endif /* INTERNAL_DATA_H_ */
