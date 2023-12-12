#include "header.h"

/**
 * change_directory - changes current directory based on user input
 *
 * @datash: data relevant
 * Return: 1 on success, -1 on failure
 */
int change_directory(data_shell *datash)
{
char *dir = datash->args[1];

if (dir == NULL || is_home_directory(dir) || is_double_dash(dir))
{
if (change_directory_to_home(datash) == -1)
{
fprintf(stderr, "Error changing to home directory\n");
return (-1);
}
return (1);
}

if (is_previous_directory(dir))
{
if (change_directory_to_previous(datash) == -1)
{
fprintf(stderr, "Error changing to previous directory\n");
return (-1);
}
return (1);
}

if (is_dot_directory(dir))
{
if (change_directory_to_dot(datash) == -1)
{
fprintf(stderr, "Error changing to dot directory\n");
return (-1);
}
return (1);
}

if (change_directory_to(datash) == -1)
{
fprintf(stderr, "Error changing to specified directory\n");
return (-1);
}
return (1);
}
