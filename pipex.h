#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft/libft.h" // Assuming you have libft in your project
#include "utils.h"
void error_exit(const char *message);
void execute_command(char *cmd, char **envp);

#endif

