/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** function.h
*/

#ifndef FUNCTION_H_
#define FUNCTION_H_

static inline void *get_in_args(char *line)
{
    u_char i = 0;
    void *data = get_args()[my_getnbr(line)];

    while (line[++i] != '\0' && line[i] != '.');
    if (line[i++] == '.') {
        line = my_strdup(line + i);
        data = get_data(line, data);
        free(line);
    }
    return (data);
}

static inline fdata_t convert_to_farg(char *arr, executor_t *executor)
{
    switch (*arr) {
        case '$':
            return ((fdata_t) {get_data(arr + 1, executor->var), 1});
        case '=':
            return ((fdata_t) {(char *) my_getnbr(arr + 1), 1});
        case '&':
            return ((fdata_t) {get_from_dict((dict_t *) executor->cmd,
                arr + 1), 1});
        case '@':
            return ((fdata_t) {my_tmpdup(arr + 1), 0});
        default:
            return ((fdata_t) {my_tmpdup(arr), 1});
    }
}

static inline fdata_t *convert_to_fargs(char **arr, executor_t *executor)
{
    fdata_t *data = malloc(sizeof(fdata_t) * (long) arr[-1]);

    if (data == NULL)
        return (NULL);
    *data = (fdata_t) {arr[0], (long) arr[-1]};
    for (u_char i = 0; ++i < data->is_complete;) {
        data[i] = convert_to_farg(arr[i], executor);
    }
    free(arr - 1);
    return (data);
}

static inline void build_func_line(func_t **func, char *line,
    executor_t *executor)
{
    func_t *new = malloc(sizeof(func_t));
    char **arr = line_to_arr(line, ' ');

    if (new == NULL || arr == NULL)
        return;
    new->next = *func;
    *arr = get_from_dict((dict_t *) executor->cmd, *arr);
    new->data = convert_to_fargs(arr, executor);
    *func = new;
}

#endif /* FUNCTION_H_ */
