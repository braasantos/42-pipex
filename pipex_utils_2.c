#include "pipex.h"

void	ft_free_cmd(t_pipex ppx)
{
	waitpid(-1, NULL, 0);
	free(ppx.cmd1);
	free(ppx.cmd2);
}

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

void	first_c(char *av, t_pipex ppx, char **envp)
{
	ft_close1(ppx);
	ft_child1(envp, av, ppx);
}

void 	second_c(char *av, char **envp, int j, t_pipex ppx)
{
	ppx.child2 = fork();
	if (ppx.child2 == 0)
	{
		if (j == (ppx.ac - 1))
			ft_closefinal(ppx);
		else
			ft_close1(ppx);
		ft_child2(envp, av, ppx);
	}
	else
		ft_free_cmd(ppx);
}

void	ft_checkfd(t_pipex ppx, char **av)
{
	if (ppx.fd0 == -1 || access(av[1], R_OK) == -1)
	{
		av[1] = ft_strjoin(av[1], ": ");
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free(av[1]);
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
		free(av[4]);
		close(ppx.fd0);
		close(ppx.fd1);
		exit(1);
	}
}
