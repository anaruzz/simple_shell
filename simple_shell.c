#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include "shell.h"
#define BUFFER_LEN 1024

	

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
	perror("failed to allocate memory for tokens\n");
	exit(EXIT_FAILURE);
}
/*signal(SIGINT, sig_handler);*/
while (1)
{
	printf("$ ");
	if ((read = getline(&line, &length, stdin)) == EOF)
	{
		printf("\n");
		exit(0);
	}
	if (read == -1)
	{
		fprintf(stderr, "lsh: unable to read command\n");
		exit(EXIT_FAILURE);
	}

	length = strlen(line);
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
{
perror("command: not found\n");
exit(127);
}
execute(argvv);
}
}
free(argvv);
return (0);
}
