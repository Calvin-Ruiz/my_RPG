/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** executor.h
*/

#ifndef EXECUTOR_H_
#define EXECUTOR_H_

#include <dict.h>

typedef struct rec_dict {
    struct rec_dict *next;
    struct rec_dict *dict;
    char *name;
} rdict_t;

typedef struct command_dict {
    struct command_dict *next;
    void (*cmd)(char **arr, rdict_t *vars);
    char *name;
} cdict_t;

typedef struct func {
    struct func *next;
    void (*cmd)(char **arr, rdict_t *vars);
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
void load_config(void);
trace_t **get_trace(void);
void set_traced_var(char *name, void *var, long filter);
void set_traced_var_cmd(char **arr, rdict_t *vars);
void trace_thread(void *ptr);
rdict_t *get_from_rec_dict(rdict_t *dict, char *name);
void call_function(char **arr, rdict_t *var);
void build_function(char *filename, executor_t *executor);

#endif /* EXECUTOR_H_ */
