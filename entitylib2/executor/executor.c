/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** executor.c
*/

#include <executor.h>
#include <tools.h>
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
        dict->cmd(arr, executor->var);
        break;
    }
    free(arr - 1);
}

static void execute_file(char *filename, executor_t *executor)
{
    int fd = open(filename, O_RDONLY);
    long len = 0;
    char *str = my_read(fd, &len);
    char **arr;

    if (str == NULL)
        return;
    str[len] = '\0';
    arr = line_to_arr(str, '\n');
    if (arr == (char **) sizeof(char *))
        return;
    for (short i = -1; arr[++i] != NULL;)
        execute_line(arr[i], executor);
    free(str);
    free(arr - 1);
    close(fd);
}

void load_config(void)
{
    executor_t *executor = get_executor();
    DIR *dir = opendir("config");
    struct dirent *dirent;
    short i = -1;

    if (dir == NULL)
        return;
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
