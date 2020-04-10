/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** executor.c
*/

#include <entitybase.h>
#include <executor.h>
#include <dirent.h>
#include <fcntl.h>
#include <my_read.h>

executor_t *get_executor(void)
{
    static executor_t executor = {NULL, NULL};

    return (&executor);
}

void execute_line(char *line, executor_t *executor)
{
    char **arr;
    cdict_t *dict = executor->cmd;

    if (*line == '#' || *line == '\0')
        return;
    arr = line_to_arr(line, ' ');
    if (arr == NULL)
        return;
    while (dict) {
        if (my_strcmp(*arr, dict->name)) {
            dict = dict->next;
            continue;
        }
        eval_args(arr, executor);
        dict->cmd(arr);
        break;
    }
    free(arr - 1);
}

static void execute_file(char *filename, executor_t *executor)
{
    int fd = open(filename, O_RDONLY);
    long len = 0;
    char *str = my_read(fd, &len);
    char **arr = line_to_arr(str, '\n');

    if (arr == NULL)
        return;
    close(fd);
    my_puterr("====== Execute file '");
    my_puterr(filename);
    my_puterr("' ======\n");
    for (short i = -1; arr[++i] != NULL;)
        execute_line(arr[i], executor);
    free(str);
    free(arr - 1);
    my_puterr("=============================================\n\n");
}

void thread_cmd(char **arr)
{
    rdict_t *var = get_executor()->var;
    sfThread *thread = get_data(tmpcat("thread.", arr[1]), var);

    if (my_strcmp(arr[2], "create") == 0) {
        thread = sfThread_create((void (*)(void *)) get_from_dict(
            (dict_t *) get_executor()->cmd, arr[3]), arr[4]);
        if (thread == NULL)
            return;
        append_to_dict((dict_t **) get_ptr_from_dict((dict_t *) var, "thread"),
            arr[1], thread);
        return;
    }
    if (thread == NULL)
        return;
    if (my_strcmp(arr[2], "run") == 0)
        sfThread_launch(thread);
    if (my_strcmp(arr[2], "wait") == 0)
        sfThread_wait(thread);
}

void load_config(executor_t *executor)
{
    DIR *dir = opendir("config");
    struct dirent *dirent;
    short i = -1;

    if (dir == NULL)
        return;
    execute_file("config/config.init", executor);
    for (dirent = readdir(dir); dirent; dirent = readdir(dir)) {
        for (i = -1; dirent->d_name[++i] != '.' && dirent->d_name[i] != '\0';);
        if (my_strcmp(dirent->d_name + i, ".func") == 0)
            build_function(dirent->d_name, executor);
    }
    closedir(dir);
    dir = opendir("config");
    for (dirent = readdir(dir); dirent; dirent = readdir(dir)) {
        for (i = -1; dirent->d_name[++i] != '.' && dirent->d_name[i] != '\0';);
        if (my_strcmp(dirent->d_name + i, ".conf") == 0)
            execute_file(tmpcat("config/", dirent->d_name), executor);
    }
    closedir(dir);
}
