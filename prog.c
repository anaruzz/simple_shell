#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFFER_LEN 1024
/**
 *main - fn - int
 *Return: int
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
	while(1)
	{
		printf("shell$ ");
		if((( read = getline(&line, &length , stdin)) < -1))
			break;
		length = strlen(line);
		if (line[length - 1] == '\n')
			line[length - 1] = '\0';
		token = strtok(line," ");
		i=0;
		while(token!=NULL)
		{
			argvv[i]= token;
			token = strtok(NULL," ");
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
		argvv[i]='\0';
		pid= fork();
		if(pid==0){
			execve(argvv[0], argvv, NULL);
			fprintf(stderr, "Child process could not do execve\n");

		}
		else
		{
			wait(NULL);
			printf("Child exited\n");
		}

		/*if(getcwd(*argvv,sizeof(argvv)) == NULL)*/ 				
			/*perror("getcwd(): error\n");*/

	}
	return (0);
}




char *tok( 

