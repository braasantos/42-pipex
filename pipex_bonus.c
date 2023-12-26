#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	ppx;

	ppx.ac = ac - 3;
	if (ac < 5 || !av[4][0])
		return (127);
	if (!av[2][0]|| !av[1][0])
		return (1);
	ppx.fd0 = open(av[1], O_RDONLY);
	ppx.fd1 = open(av[ac -1], O_CREAT | O_RDWR | O_TRUNC, 0664);
	check_file(av, ppx);
	ft_checkfd(ppx, av);
	pipex(envp, av, ppx);
	return (0);
}