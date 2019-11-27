#include "shell.h"

/**
* sig_handler - checks if Ctrl C is pressed
* @sig_num: int
*/
void sig_handler(int sig_num)
{
if (sig_num == SIGINT)
write(1, "\n$ ", 3);
}


/**
*main - main program for the shell project
*
*Return: 0
*/
int main(void)
{
int bufsize = BUFFER_LEN, i;
char **argvv;
char *line;
struct stat sfile;

signal(SIGINT, sig_handler);
while (1)
{
write(STDOUT_FILENO, "$ ", 2);

line = read_line();

argvv = split_line(line, bufsize);
i = check_builtin(argvv[0]);
if (i >= 0)
builtins(argvv, i);
else
{
if (stat(argvv[0], &sfile) != 0)
{
argvv[0] = find_path(argvv[0]);
if (argvv[0] == NULL)
{
perror(argvv[0]);
free(argvv);
}
}

exec_command(argvv);
}
}
free(line);
free(argvv);
return (0);
}
