/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** dynamic_structures.c
*/

#include <executor.h>
#include <dynamic_structures.h>

void *build_struct(char *str)
{
    static char buffer[1024*4];
    char *target = buffer;
    char *ptr = target;
    char **arr = line_to_arr(str, '|');
    executor_t *executor = get_executor();
    u_char i = 0;
    for (i = -1; str[++i] != '}' && str[i] != '\0';);
    if (str[i] == '}' && str[i + 1] == '!') {
        target = my_malloc(my_getnbr(str + i + 2));
        ptr = target;
    }
    str[i] = '\0';
    for (u_char j = -1; arr[++j];) {
        for (i = -1; arr[j][++i] != ':';);
        arr[j][i++] = '\0';
        insert_data(&ptr, get_data_len(arr[j], (dict_t *) executor->var),
            eval_arg(arr[j]+i, executor));
    }
    free(arr - 1);
    return (target);
}

float get_float(char *str)
{
    float val = 0;
    char is_neg = 0;
    char decremential = 0;

    if (*str == '-') {
        is_neg = 1;
        str++;
    }
    while (*str) {
        if (*str == '.' || decremential)
            str += (decremential++ == 0);
        val = val * 10.f + (*str - '0');
    }
    while (decremential-- > 0)
        val /= 10.f;
    return ((is_neg) ? -val : val);
}

double get_double(char *str)
{
    double val = 0;
    char is_neg = 0;
    char decremential = 0;

    if (*str == '-') {
        is_neg = 1;
        str++;
    }
    while (*str) {
        if (*str == '.' || decremential)
            str += (decremential++ == 0);
        val = val * 10. + (*str - '0');
    }
    while (decremential-- > 0)
        val /= 10.;
    return ((is_neg) ? -val : val);
}
