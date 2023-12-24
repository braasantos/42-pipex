#include "pipex.h"

void	ft_close_and_exit1(t_pipex ppx, char *av2)
{
	close(ppx.fd0);
	close(ppx.fd1);
	close(ppx.end[0]);
	close(ppx.end[1]);
	ft_putstr_fd(av2, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	ft_close_and_exit2(t_pipex ppx, char *av3)
{
	close(ppx.fd0);
	close(ppx.fd1);
	close(ppx.end[0]);
	close(ppx.end[1]);
	ft_putstr_fd(av3, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	check_file(char **av, t_pipex ppx)
{
	if (access(av[1], F_OK) == -1)
	{
		av[1] = ft_strjoin(av[1], ": ");
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free(av[1]);
		close(ppx.fd0);
		close(ppx.fd1);
		exit(1);
	}
}
