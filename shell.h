#ifndef SHELL_H
#define SHELL_H

// Required headers
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Function declarations
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_launch(char **args);
int shell_execute(char **args);
char *shell_readLine(void);
char **shell_Split_Line(char *line);
void shell_cycle(void);

#endif // SHELL_H
