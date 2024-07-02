#include "pipex.h"

/// @brief			Close the file descriptors and exit the program
/// @param ppx		The structure containing the file descriptors
/// @param av		The command that was not found
void	ft_close_and_exit(t_pipex ppx, char *av)
{
	close(ppx.fd0);
	close(ppx.fd1);
	close(ppx.end[0]);
	close(ppx.end[1]);
	ft_putstr_fd(av, 2);
	ft_putstr_fd(": command not found\n", 2);
}

/// @brief			Function to check if the file exists
/// @param ppx		The structure containing the file descriptors
/// @param av		Array of Arguments
void	check_file(t_pipex ppx, char *av)
{
	if (access(av, F_OK) == -1)
	{
		av = ft_strjoin(av, ": ");
		ft_putstr_fd(av, 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		close(ppx.fd0);
		close(ppx.fd1);
		exit(1);
	}
}
/// @brief			Free the commands
/// @param ppx		The structure with tthe commands
void	free_cmd(t_pipex ppx)
{
	if (ppx.cmd1)
		free(ppx.cmd1);
	if (ppx.cmd2)
		free(ppx.cmd2);
}

/// @brief			Function to print the error message when the command is not found
/// @param av1		The first command
/// @param av2		The second command
/// @param ppx		The structure with the file descriptors
void	cmd_notfound(t_pipex ppx, char *av1, char *av2)
{
	close(ppx.fd0);
	close(ppx.fd1);
	ft_putstr_fd(av1, 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_putstr_fd(av2, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_cmd(ppx);
	exit(127);
}