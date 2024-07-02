#include "pipex.h"

/// @brief			Original main function for the mandatory part
/// @param ac		Number of arguments
/// @param av		Array of Arguments
/// @param envp		Array of environment variables
/// @return			0 if successful, 127 or 1 if not
int	main(int ac, char **av, char **envp)
{
	t_pipex	ppx;

	ppx.ac = ac - 3;
	if (ac != 5 || !av[4][0])
		return (127);
	if (!av[2][0]|| !av[1][0] || !av[3][0])
		return (1);
	ppx.fd0 = open(av[1], O_RDONLY);
	ppx.fd1 = open(av[ac -1], O_CREAT | O_RDWR | O_TRUNC, 0664);
	check_file(ppx, av[1]);
	check_fds(ppx, av);
	pipex(ppx, envp, av);
	return (0);
}