/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:41:33 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/23 21:23:24 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path_og(char **envp)
{
	int		i;
	char	*str;
	char	**newstr;

	i = 0;
	newstr = NULL;
	if (!envp[i])
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			str = ft_substr(envp[i], 5, ft_strlen(envp[i]));
		i++;
	}
	if (str)
		newstr = ft_split(str, ':');
	free(str);
	return (newstr);
}
char	*ft_add_og(char **envp, char *ag)
{
	char	*cmd1;
	char	**str;
	char	**args;
	char	*tmp;
	int		i;

	i = 0;
	str = get_path_og(envp);
	args = ft_split(ag, ' ');
	if (!*str)
		return (NULL);
	while (str[i])
	{
		tmp = ft_strjoin(str[i], "/");
		cmd1 = ft_strjoin(tmp, args[0]);
		free(tmp);
		if (access(cmd1, X_OK) == 0)
			return (ft_free_str_og(args), ft_free_str_og(str), cmd1);
		free(cmd1);
		i++;
	}
	ft_free_str_og(args);
	ft_free_str_og(str);
	return (NULL);
}
void	pipex_og(char **envp, char **av, t_pipex ppx)
{
	pid_t	child;
	pid_t	child2;
	char	*cmd1;
	char	*cmd2;

	if (pipe(ppx.end) == -1)
		exit(1);
	child = fork();
	if (child == 0)
	{
		ft_close1_og(ppx);
		ft_child1_og(envp, (cmd1 = cmd_is_ok(envp, av, 2)), av[2], ppx);
	}
	else
	{
		child2 = fork();
		if (child2 == 0)
		{
			ft_close2_og(ppx);
			ft_child2_og(envp, (cmd2 =  cmd_is_ok(envp, av, 3)), av[3], ppx);
		}
		else
			ft_free_cmd_og(cmd1 = ft_add_og(envp, av[2]), cmd2 = ft_add_og(envp, av[3]));
	}
}
void	ft_checkfd_og(t_pipex ppx, char **av)
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
        exit(0); //0
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
        exit(1); //1
    }
}
int	main(int ac, char **av, char **envp)
{
	t_pipex ppx;
	
	if (ac != 5 || !av[4][0])
		return (0); //0
	if (av[2][0] == '\0' || !av[1][0])
		return (0); //0
	ppx.fd0 = open(av[1], O_RDONLY);
	ppx.fd1 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (access(av[1], F_OK) == -1)
	{
		av[1] = ft_strjoin(av[1], ": ");
    ft_putstr_fd(av[1], 2);
  	ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
    free(av[1]);
    close(ppx.fd0);
    close(ppx.fd1);
		exit(1); //1
	}
	ft_checkfd_og(ppx, av);
	pipex_og(envp, av, ppx);
	return (0);
}
