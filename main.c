#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	int pipefd[2];
	pid_t pid1, pid2;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	if (pipe(pipefd) == -1)
		error_exit("Pipe error");

	pid1 = fork();
	if (pid1 == -1)
		error_exit("Fork error");

	if (pid1 == 0)
	{
		int file_in = open(argv[1], O_RDONLY);
		if (file_in < 0)
			error_exit("Error opening input file");

		dup2(file_in, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		close(file_in);
		execute_command(argv[2], envp);
	}

	pid2 = fork();
	if (pid2 == -1)
		error_exit("Fork error");

	if (pid2 == 0)
	{
		int file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file_out < 0)
			error_exit("Error opening output file");

		dup2(pipefd[0], STDIN_FILENO);
		dup2(file_out, STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		close(file_out);
		execute_command(argv[3], envp);
	}

	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
}

