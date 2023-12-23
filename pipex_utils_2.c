#include "pipex.h"

void	ft_close_and_exit2(t_pipex ppx, char *av3)
{
	close(ppx.fd0);
	close(ppx.fd1);
	close(ppx.end[0]);
	close(ppx.end[1]);
	ft_putstr_fd(av3, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
}
void	ft_close_and_exit1(t_pipex ppx, char *av2)
{
	close(ppx.fd0);
	close(ppx.fd1);
	close(ppx.end[0]);
	close(ppx.end[1]);
	ft_putstr_fd(av2, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
}
char	*cmd_is_ok(char **envp, char **av, int n)
{
	char *cmd;
	char *cmd2;

	if (n == 2)
	{
		cmd = ft_add_og(envp, av[2]);
		if (cmd == NULL)
			return (NULL);
		return (cmd);
	}
	else
	{
		cmd2 = ft_add_og(envp, av[3]);
		if (cmd2 == NULL)
			return (NULL);
		return (cmd2);
	}
}
void	ft_free_str_og(char **str)
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
