#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define BUFFER_LEN 1024


char *concat_all(char *s1, char *s2)
{
	char *result;
	int l1, l2, i, k;

for(l1 = 0; s1[l1]; l1++)
;

for(l2 = 0; s2[l2]; l2++)
;


	result = malloc(l1 + l2 + 1);
	if (!result)
		return (0);

	for (i = 0; s1[i]; i++)
		result[i] = s1[i];
	k = i;

	for (i = 0; s2[i]; i++)
		result[k + i] = s2[i];
	k = k + i;

	result[k] = '\0';

	return (result);
}



char *find_path(char *av)
{
char *path, *token, *cpath;
int i, len = 0;
struct stat sfile;

path = getenv("PATH");
for (len = 0; path[len]; len++)
;

cpath = malloc(sizeof(char) * len +1);

for (i = 0; path[i]; i++)
cpath[i] = path[i];
cpath[i] = '\0';


  token = strtok(cpath, ":");
token = concat_all(token, "/");
token = concat_all(token, av);

  while (token != NULL)
  {
    if (stat(token, &sfile) == 0)

			return (token);

    token = strtok(NULL, ":");
    token = concat_all(token, "/");
  token = concat_all(token, av);
  }

  return (NULL);
}

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
	int bufsize = BUFFER_LEN, pid, read;
	char **argvv = malloc(sizeof(char) * bufsize);
	char *line;
	size_t length = 0;



	if (!argvv)
	{
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		printf("$ ");

		if ((read = getline(&line, &length, stdin))== EOF)
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
//if it's not a builtin or an alias
//look for path

if ((argvv[0] = find_path(argvv[0])) == NULL)
{
	fprintf(stderr, "Command not found\n");
	exit(127);
}

		pid = fork();
		if (pid == 0)
		{
			if (execve(argvv[0], argvv, NULL) == -1)
			fprintf(stderr, "Child process could not do execve\n");
		}
		else if (pid == -1)
			fprintf(stderr, "Child process does not exit\n");
		else
			wait(NULL);
	}
	return (0);
}
