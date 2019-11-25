#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFFER_LEN 1024

/**
 * tokenize - parse the input string
 * @line: string
 * @argvv: array of strings to fill
 * @bufsize: size of buffer for allocation
 *Return: void
 */
void tokenize(char *line, char **argvv, int bufsize)
{
	char *token;
	int	i = 0;

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
				fprintf(stderr, "shell: Allocation error!\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	argvv[i] = '\0';
}

/**
 *main - main program for the shell project
 *
 *Return: 0
 */
int main(void)
{
	int bufsize = BUFFER_LEN, i, pid, read;
	char **argvv = malloc(sizeof(char) * bufsize);
	char *token, *line;
	size_t length = 0;

	if (!argvv)
	{
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		printf("$ ");
		read = getline(&line, &length, stdin);
		if (read < -1)
			break;
		length = strlen(line);
		if (line[length - 1] == '\n')
			line[length - 1] = '\0';

		tokenize(line, argvv, bufsize);


		pid = fork();
		if (pid == 0)
		{
			if (execve(argvv[0], argvv, NULL) == -1)
			fprintf(stderr, "Child process could not do execve\n");
		}
		else
		{
			wait(NULL);
		}

	

	}
	return (0);
}
