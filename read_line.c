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
if (read == EOF)
{
write(STDERR_FILENO, "\n", 1);
exit(0);
}
if (read == -1)
{
write(STDERR_FILENO, "hsh: unable to read command\n", 29);
exit(EXIT_FAILURE);
}
length = _strlen(line);
if (line[length - 1] == '\n')
line[length - 1] = '\0';

return (line);
}
