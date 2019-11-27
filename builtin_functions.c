#include "shell.h"



/**
 * print_env - print all environment variables
 *
 *Return: Void
 */
void print_env(void)
{
	extern char **environ;
	int i;
	char *s = *environ;

	for (i = 1; s != NULL; i++)
	{
		printf("%s\n", s);
		s = environ[i];
	}

}


/**
 * change_dir - change directory with builtin cd
 * argvv: array of string arguments
 *Return: Void
 */
void change_dir (char **argvv)
{
	char *pth;
	int i, j;
	if (argvv[1] == NULL)
		pth = getenv("HOME");
	else if (_strcmp(argvv[1], "-") == 0)
	{
		pth = getenv("PWD");
		for (i = 0; pth[i]; i++)
			;
		for (j = i; pth[j] != '/'; j--)
			;
		if (pth[j] == '/')
			pth[j] = '\0';
	}
	else
		pth = argvv[1];
	if (chdir(pth) == -1)
		perror("lsh");
	setenv("PWD", pth, 1);
}

/**
  * __exit - exit with status given in arguments
  * @argvv:array of strings to execute builtin
  *Return: Void
 */
void __exit (char **argvv)
{
	if (argvv[1] == NULL)
		exit(0);
	else
		exit(_atoi(argvv[1]));
}


/* Function to execute builtin */
/**
 * builtins - execute builtins
 * @argvv:array of strings to execute builtin
 *Return: Void
 */
void builtins(char **argvv, int i)
{

	switch (i)
	{
		case 1:
			__exit(argvv);
			break;
		case 2:
			change_dir(argvv);
			break;
		case 3:
			puts("shell: help: not found");
			break;
		case 4:
			print_env();
			break;
		default:
			break;
	}

}