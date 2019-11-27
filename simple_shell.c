#include "shell.h"

/**
*main - main program for the shell project
*
*Return: 0
*/
int main(void)
{
int bufsize = BUFFER_LEN, read, i;
char **argvv = malloc(sizeof(char) * bufsize);
char *line = NULL;
size_t length = 0;
if (!argvv)
{
	 write(STDERR_FILENO, "hsh: allocation error\n", 22);
	exit(EXIT_FAILURE);
}
while (1)
{
	write(STDOUT_FILENO, "$ ", 2);
	if ((read = getline(&line, &length, stdin)) == EOF)
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
	tokenize(line, argvv, bufsize);
i = check_builtin(argvv[0]);
if (i >= 0)
builtins(argvv, i);
else
{
argvv[0] = find_path(argvv[0]);
if (argvv[0] == NULL)
perror(argvv[0]);
execute(argvv);
}
}
free(argvv);
return (0);
}
