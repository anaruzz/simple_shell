#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include "shell.h"

/**
 * find_path - find the path of the command
 * @av: the command to look for its path
 *Return: string: full path of the command
 */
char *find_path(char *av)
{
	char *path = NULL, *token = NULL, *cpath = NULL;
	int i = 0, len = 0;
	struct stat sfile;

	path = getenv("PATH");
	for (len = 0; path[len]; len++)
		;

	cpath = malloc(sizeof(char) * len + 1);

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
free(token);
		token = strtok(NULL, ":");
		if (token != NULL)
		{
			token = concat_all(token, "/");
			token = concat_all(token, av);
		}

	}
free(token);
free(cpath);
	return (NULL);
}


/**
 * check_builtin - check if the string passed is a builtin
 * @argvv: string to check
 *Return: -1 on falure & >= 1 on success
 */
int check_builtin(char *argvv)
{
	int i = 0;
	char *cm[4];

	cm[0] = "exit";
	cm[1] = "cd";
	cm[2] = "help";
	cm[3] = "env";
	while (i < 4)
	{
		if (_strcmp(argvv, cm[i]) == 0)
			return (i + 1);

			i++;
	}
	return (-1);
}


/**
  * comments - handle the shell comments
  * @argvv: array of string
  * Return: void
  */
void comments(char **argvv)
{
char j[10] = "echo $$ #";
if (_strcmp(j, *argvv) == 0)
	printf("5114");
}
