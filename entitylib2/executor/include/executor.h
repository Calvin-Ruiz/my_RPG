/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** executor.h
*/

#ifndef EXECUTOR_H_
#define EXECUTOR_H_

#include <dict.h>
#include <tools.h>
#include <my_getnbr.h>

enum {
    UCHAR,
    SHORT,
    INT,
    LONG,
    FLOAT,
    DOUBLE,
};

typedef struct rec_dict {
    struct rec_dict *next;
    struct rec_dict *dict;
    char *name;
} rdict_t;

typedef struct command_dict {
    struct command_dict *next;
    void (*cmd)(char **arr);
    char *name;
} cdict_t;

typedef struct function_data {
    void *data;
    char is_complete;
} fdata_t;

typedef struct func {
    struct func *next;
    fdata_t *data;
} func_t;

typedef struct my_trace {
    struct my_trace *next;
    long *var;
    char *name;
    long filter;
} trace_t;

typedef struct walk {
    struct walk *next;
} walk_t;

typedef struct executor {
    rdict_t *var;
    cdict_t *cmd;
} executor_t;

executor_t *get_executor(void);
void *get_data(char *name, rdict_t *var);
void execute_line(char *line, executor_t *executor);
void build_function(char *filename, executor_t *executor);
void load_config(executor_t *executor);
trace_t **get_trace(void);
void set_traced_var(char *name, void *var, long filter);
void set_traced_var_cmd(char **arr);
void trace_thread(void *ptr);
rdict_t *get_from_rec_dict(rdict_t *dict, char *name);
void call_function(char **arr);
void build_function(char *filename, executor_t *executor);
void set_value(char **arr);
void create_variable(char **arr);
void thread_cmd(char **arr);
char **get_args(void);
void append_to_list_cmd(char **args);
void init_executor(void);
void init_external_cmds(dict_t **cmd);
dict_t *get_internal_func(void);
dict_t *define_structs(void);
void new_entity(char **arr);
void put_in_log(char **arr);
void sleep_cmd(char **arr);
void *build_struct(char *str);

static inline void eval_args(char **arr, executor_t *executor)
{
    while (*++arr != NULL) {
        switch (**arr) {
            case '$':
                *arr = get_data(*arr + 1, executor->var);
                break;
            case '=':
                *arr = (char *) my_getnbr(*arr + 1);
                break;
            case '&':
                *arr = get_from_dict((dict_t *) executor->cmd, *arr + 1);
                break;
            case '@':
                *arr = (char *) (get_args() + my_getnbr(*arr + 1));
                break;
            case '{':
                *arr = (char *) build_struct(*arr + 1);
                break;
        }
    }
}

static inline void put_traced_nbr(void *nbr, char type)
{
    switch (type) {
        case UCHAR:
            my_putnbr(*(u_char *) nbr);
            break;
        case SHORT:
            my_putnbr(*(short *) nbr);
            break;
        case INT:
            my_putnbr(*(int *) nbr);
            break;
        case LONG:
            my_putnbr(*(long *) nbr);
            break;
        case FLOAT:
            my_putnbr(*(float *) nbr);
            break;
        case DOUBLE:
            my_putnbr(*(double *) nbr);
            break;
    }
}

static inline u_char get_in_struct(char **arr)
{
    dict_t *dict = get_from_dict(get_from_dict((dict_t *)
        get_executor()->var, "struct"), (*arr) + 1);

    if (dict == NULL) {
        my_puterr("\e[95mCastError : Structure '");
        my_puterr((*arr) + 1);
        my_puterr("' is unreferenced.\n\e[0m");
    }
    return ((long) get_from_dict(dict, arr[1]));
}

#endif /* EXECUTOR_H_ */
