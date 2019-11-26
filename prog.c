#include <stdio.h>                              
#include <stdlib.h>                             
#include <string.h>                             
#include <unistd.h>                             
#include <sys/types.h>                          
#include <sys/wait.h>                           
#include <sys/stat.h>                           
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

