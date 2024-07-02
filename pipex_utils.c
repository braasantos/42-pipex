#include "pipex.h"

/// @brief			Fuction to free the command strings and wait for the child process
/// @param ppx		The structure containing the command strings
void	wait_child(t_pipex ppx)
{
	waitpid(-1, NULL, 0);
	free(ppx.cmd1);
	free(ppx.cmd2);
}

/// @brief			Function to free an array of strings
/// @param str		The array of strings
void	ft_free_str(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

/// @brief			Function to Handle the first command in the pipeline
/// @param av		The command to execute
/// @param ppx		The structure containing the data
/// @param envp		The environment variables
void	st_cmd(t_pipex ppx, char *av, char **envp)
{
	first_cmd(ppx);
	child1(ppx, envp, av);
}

/// @brief			Function to Handle the second command in the pipeline 
/// @param av		The command to execute
/// @param envp		The environment variables
/// @param j		The index of the command
/// @param ppx		The structure containing the data
void 	second_cmd( t_pipex ppx, char *av, char **envp, int j)
{
	ppx.child2 = fork();
	if (ppx.child2 == 0)
	{
		if (j == (ppx.ac - 1))
			last_cmd(ppx);
		else
			first_cmd(ppx);
		child2(ppx, envp, av);
	}
	else
		wait_child(ppx);
}

/// @brief			Function to check if the file descriptor of the files are valid
/// @param ppx		The structure containing the file descriptors
/// @param av		Array of Arguments
void	check_fds(t_pipex ppx, char **av)
{
	if (ppx.fd0 == -1 || access(av[1], R_OK) == -1)
	{
		av[1] = ft_strjoin(av[1], ": ");
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		close(ppx.fd0);
		close(ppx.fd1);
		exit(0);
	}
	if (ppx.fd1 < 0)
	{
		av[4] = ft_strjoin(av[4], ": ");
		ft_putstr_fd(av[4], 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		close(ppx.fd0);
		close(ppx.fd1);
		exit(1);
	}
}
