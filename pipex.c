#include "pipex.h"
#include "utils.h" // Include the utils header

void error_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void execute_command(char *cmd, char **envp)
{
	(void)envp; // Mark envp as unused
	char **cmd_args = ft_split(cmd, ' ');

	if (!cmd_args || !cmd_args[0])
	{
		ft_putstr_fd("Command not found or not executable: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}

	execvp(cmd_args[0], cmd_args);
	ft_free_split(cmd_args);
	error_exit("Error executing command");
}

