/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** system_cmd.h
*/

#ifndef SYSTEM_CMD_H_
#define SYSTEM_CMD_H_

#include <executor.h>

static inline long get_value_from_basic_type(char **arr)
{
    switch ((char) (long) arr[0]) {
        case UCHAR:
            return (*(u_char *) arr[1]);
        case CHAR:
            return (*(char *) arr[1]);
        case USHORT:
            return (*(u_short *) arr[1]);
        case SHORT:
            return (*(short *) arr[1]);
        case RAW:
            return (*(u_int *) arr[1]);
        case INT:
            return (*(int *) arr[1]);
        case LONG:
            return (*(long *) arr[1]);
        case FLOAT:
            return (*(float *) arr[1]);
        case DOUBLE:
            return (*(double *) arr[1]);
    }
}

static inline double get_value_from_floating_type(char **arr)
{
    switch ((char) (long) arr[0]) {
        case UCHAR:
            return (*(u_char *) arr[1]);
        case CHAR:
            return (*(char *) arr[1]);
        case USHORT:
            return (*(u_short *) arr[1]);
        case SHORT:
            return (*(short *) arr[1]);
        case RAW:
            return (*(u_int *) arr[1]);
        case INT:
            return (*(int *) arr[1]);
        case LONG:
            return (*(long *) arr[1]);
        case FLOAT:
            return (*(float *) arr[1]);
        case DOUBLE:
            return (*(double *) arr[1]);
    }
}

static inline void set_value_from_basic_type_part(char **arr, long value)
{
    switch ((char) (long) arr[0]) {
        case INT:
            *(int *) arr[1] = value;
            return;
        case LONG:
            *(long *) arr[1] = value;
            return;
        case FLOAT:
            *(float *) arr[1] = value;
            return;
        case DOUBLE:
            *(double *) arr[1] = value;
            return;
        default:
            return;
    }
}

static inline void set_value_from_basic_type(char **arr, long value)
{
    switch ((char) (long) arr[0]) {
        case UCHAR:
            *(u_char *) arr[1] = value;
            return;
        case CHAR:
            *(char *) arr[1] = value;
            return;
        case USHORT:
            *(u_short *) arr[1] = value;
            return;
        case SHORT:
            *(short *) arr[1] = value;
            return;
        case UINT:
            *(u_int *) arr[1] = value;
            return;
        default:
            set_value_from_basic_type_part(arr, value);
    }
}

static inline void set_value_from_floating_type(char **arr, double value)
{
    switch ((char) (long) arr[0]) {
        case FLOAT:
            *(float *) arr[1] = value;
            return;
        case DOUBLE:
            *(double *) arr[1] = value;
            return;
    }
}

void better_operator(char **arr);
void float_operator(char **arr);
void set_from_var(char **arr);
void read_cmd(char **arr);
void write_cmd(char **arr);
void putstr_cmd(char **arr);
void open_cmd(char **arr);
void close_cmd(char **arr);
void randint_cmd(char **arr);

#endif /* SYSTEM_CMD_H_ */
