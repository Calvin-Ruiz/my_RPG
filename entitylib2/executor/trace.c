/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** trace.c
*/

#include <executor.h>
#include <dynamic_printer.h>
#include <my_getnbr.h>
#include <entitybase.h>
#include <data_storage.h>

trace_t **get_trace(void)
{
    static trace_t *trace = NULL;

    return (&trace);
}

void set_traced_var(char *name, void *var, long filter)
{
    trace_t **trace = get_trace();
    trace_t *new = my_malloc(sizeof(trace_t));

    if (var == NULL) {
        my_puterr("\e[94mTraceError : nullptr received for trace '");
        my_puterr(name);
        my_puterr("'\n\e[0m");
        return;
    }
    new->next = *trace;
    new->name = my_strdup(name);
    new->filter = filter;
    new->var = var;
    *trace = new;
}

void set_traced_var_cmd(char **arr)
{
    if ((long) arr[-1] != 4)
        return;
    set_traced_var(arr[1], arr[2], (long) arr[3]);
}

static void update_trace(trace_t *trace)
{
    short heigh = 3;
    trace_t *tmp = trace;

    while (tmp) {
        heigh++;
        tmp = tmp->next;
    }
    draw_cadre(48, heigh);
    my_move(2, 1);
    while (trace) {
        my_set_color(FOREGROUND_LIGHT + BLUE);
        my_putstr(trace->name);
        my_set_color(FOREGROUND_DARK + WHITE);
        write(1, " = ", 3);
        my_set_color(FOREGROUND_LIGHT + GREEN);
        put_traced_nbr(trace->var, trace->filter);
        write(1, "\n\e[C ", 5);
        trace = trace->next;
    }
    my_set_color(FOREGROUND_LIGHT + WHITE);
}

void trace_thread(void *ptr)
{
    trace_t **trace = get_trace();
    char *is_alive = &((data_storage_t *) ptr)->is_alive;
    char *ask_command = &((data_storage_t *) ptr)->ask_command;
    char cmd[4096];
    short size = 0;

    while (*is_alive) {
        update_trace(*trace);
        sfSleep((sfTime) {50000});
        if (*ask_command == 0)
            continue;
        write(1, "\e[33m>>> \e[0m", 13);
        size = read(0, cmd, 4096);
        if (size <= 0) {
            *ask_command = 0;
            continue;
        }
        cmd[size - 1] = '\0';
        execute_line(cmd, get_executor());
    }
}
