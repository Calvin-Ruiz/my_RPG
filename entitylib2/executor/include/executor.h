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

typedef struct func {
    struct func *next;
    char **arr;
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
                *arr = get_args()[my_getnbr(*arr + 1)];
                break;
        }
    }
}

#endif /* EXECUTOR_H_ */
