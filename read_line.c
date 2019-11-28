#include <stdio.h>
#include "shell.h"

/**
* read_line - read a line from input
*
* Return: string read
*/
char *read_line(void)
{
char *line = NULL;
size_t length = 0;
int read;

read = getline(&line, &length, stdin);
// if (read == EOF)
// {
// exit(0);
// }
if (read == -1)
{
exit(0);
}
line = strtok(line, "\n");

return (line);
}
