#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h>
#include<sys/wait.h>
char *concat_all(char *s1, char *s2);
char *find_path(char *av);
void tokenize(char *line, char **argvv, int bufsize);
int main(void);


