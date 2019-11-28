#include <stdio.h>
#include "shell.h"

/**
* read_line - it reads a line from input
*
* Return: string read
*/
char *read_line(void)
{
char *line = NULL, *x = "\n";
size_t length = 0;
int read;

read = getline(&line, &length, stdin);
if (read == EOF)
{
write(1, x, 1);
exit(0);
}
if (read == -1)
exit(0);

if (line[length - 1] == '\n')
line[length - 1] = '\0';

return (line);
}
