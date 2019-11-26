#include <stdio.h>                              
#include <stdlib.h>                             
#include <string.h>                             
#include <unistd.h>                             
#include <sys/types.h>                          
#include <sys/wait.h>                           
#include <sys/stat.h>   
#include "shell.h"
#define BUFFER_LEN 1024                         

/**                                             
 * concat_all - concatenate two strings          
 * @s1: string                                   
 * @s2: string                                   
 *Return: string                                 
 */                                              
char *concat_all(char *s1, char *s2)            
{                                               
	char *result = NULL;                            
	int l1 = 0, l2 = 0, i = 0, k = 0;               

	for (l1 = 0; s1[l1]; l1++)                      
		;                                               

	for (l2 = 0; s2[l2]; l2++)                      
		;                                               

	result = malloc(sizeof(char) * (l1 + l2 + 1));  
	if (!result)                                    
		return (NULL);                          

	for (i = 0; s1[i]; i++)                         
		result[i] = s1[i];                      
	k = i;                                          

	for (i = 0; s2[i]; i++)                         
		result[k + i] = s2[i];                  
	k = k + i;                                      

	result[k] = '\0';                               

	return (result);                                
}                                               






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

		token = strtok(NULL, ":");
		if (token != NULL)
		{
			token = concat_all(token, "/");
			token = concat_all(token, av);
		}

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
	char *token = NULL;                                                          
	int     i = 0;                                                               

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
				perror("tokenize fail");                             
				exit(EXIT_FAILURE);                                  
			}                                                            
		}                                                                    
	}                                                                            
	argvv[i] = '\0';                                                             
}                                                                            

/**                                                                          
 * check_builtin - check if the string passed is a builtin                    
 * @argvv[0]: string to check                                                 
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
		if (strcmp(argvv, cm[i]) == 0)                                       
			return (i + 1);                                                      
		else                                                                 
			i++;                                                                 
	}                                                                            
	return (-1);                                                                 
}                                                                            




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
	else if (strcmp(argvv[1], "-") == 0)
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
		perror("cd: can't cd to directory");
	setenv("PWD", pth, 1);
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
			exit(atoi(argvv[1]));
			break;
		case 2:
			change_dir(argvv);
			break;
		case 3:
			puts("shell: 1: help: not found");
			break;
		case 4:
			print_env();
			break;
		default:
			break;
	}

}

/**
 * execute - execute command
 * @argvv: array of strings to check
 *Return: void
 */
void execute(char **argvv)
{
	int pid = 0;
	pid = fork();
	if (pid == 0)
	{
		if (execve(argvv[0], argvv, NULL) == -1)
		{
			perror("hsh");
			exit(0);
		}
	}
	else if (pid == -1)
	{
		perror("hsh error - child is -1");
		exit(-1);
	}
	else
		wait(NULL);
}
