/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** system_cmd_2.c
*/

#include <system_cmd.h>

void better_operator(char **arr)
{
    long var1 = get_value_from_basic_type(arr + 3);
    const long var2 = get_value_from_basic_type(arr + 6);

    if (*(arr[5]) == '+')
        var1 += var2;
    if (*(arr[3]) == '-')
        var1 -= var2;
    if (*(arr[3]) == '*')
        var1 *= var2;
    if (*(arr[3]) == '/')
        var1 /= var2;
    if (*(arr[3]) == '%')
        var1 %= var2;
    set_value_from_basic_type(arr + 1, var1);
}

void float_operator(char **arr)
{
    long var1 = get_value_from_floating_type(arr + 3);
    const long var2 = get_value_from_floating_type(arr + 6);

    if (*(arr[5]) == '+')
        var1 += var2;
    if (*(arr[3]) == '-')
        var1 -= var2;
    if (*(arr[3]) == '*')
        var1 *= var2;
    if (*(arr[3]) == '/')
        var1 /= var2;
    if (*(arr[3]) == '%')
        var1 %= var2;
    set_value_from_floating_type(arr + 1, var1);
}

void set_from_var(char **arr)
{
    set_value_from_basic_type(arr + 1, get_value_from_basic_type(arr + 3));
}

void randint_cmd(char **arr)
{
    *(int *) arr[1] = rand();
}
