#include "shell.h"

/**
* tokenize - parse the input string
* @line: string
* @argvv: array of strings to fill
* @bufsize: size of buffer for allocation
*Return: void
*/
char **split_line(char *line, int bufsize)
{
char *token = NULL;
int     i = 0;
char **argvv = malloc(sizeof(char) * bufsize);
if (!argvv)
{
write(STDERR_FILENO, "hsh: allocation error\n", 22);
exit(EXIT_FAILURE);
}

token = strtok(line, " ");
while (token != NULL)
{
argvv[i] = token;
token = strtok(NULL, " ");
i++;
if (i >= bufsize)
{
bufsize += BUFFER_LEN;
argvv = realloc(argvv, bufsize * sizeof(char *));
if (!argvv)
{
write(STDERR_FILENO, "hsh: allocation error\n", 22);
exit(EXIT_FAILURE);
}
}
}
argvv[i] = NULL;
free(token);
return(argvv);
}
