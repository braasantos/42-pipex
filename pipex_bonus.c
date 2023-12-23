/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:41:33 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/23 17:08:00 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path_bonus(char **envp)
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
void	ft_cmmd_notfound_bonus(char *av)
{
	av = ft_strjoin(av, ": ");
	ft_putstr_fd(av, 2);
	ft_putstr_fd("command not found", 2);
	ft_putstr_fd("\n", 2);
	free(av);
}
char	*ft_add_bonus(char **envp, char *ag)
{
	char	*cmd1;
	char	**str;
	char	**args;
	char	*tmp;
	int		i;

	i = 0;
	str = get_path_bonus(envp);
	args = ft_split(ag, ' ');
	if (!*str)
		return (NULL);
	while (str[i])
	{
		tmp = ft_strjoin(str[i], "/");
		cmd1 = ft_strjoin(tmp, args[0]);
		free(tmp);
		if (access(cmd1, X_OK) == 0)
			return (ft_free_str_bonus(args), ft_free_str_bonus(str), cmd1);
		free(cmd1);
		i++;
	}
	return (ft_free_str_bonus(args), ft_free_str_bonus(str), NULL);
}
void	pipex_bonus(char **envp, char **av, t_pipex ppx)
{
	int		i;
	int		j;

	i = 2;
	j = 1;
	while (j < ppx.ac)
	{
		ppx.cmd1 = ft_add_bonus(envp, av[i]);
		ppx.cmd2 = ft_add_bonus(envp, av[i + 1]);
		if (!ppx.cmd1)
			ft_cmmd_notfound_bonus(av[i]);
		if (!ppx.cmd2)
			ft_cmmd_notfound_bonus(av[i + 1]);
		if (pipe(ppx.end) == -1)
			exit(EXIT_FAILURE);
		ppx.child1 = fork();
		if (ppx.child1 == 0)
			first_c_bonus(av[i], ppx, envp);
		else
			second_c_bonus(av[i + 1], envp, j, ppx);
		i++;
		j++;
	}
}
int	main(int ac, char **av, char **envp)
{
	t_pipex	ppx;

	ppx.ac = ac - 3;
	if (ac <= 4 || !av[4][0])
		return (1);
	if (av[2][0] == '\0' || !av[1][0])
		return (0);
	ppx.fd0 = open(av[1], O_RDONLY);
	ppx.fd1 = open(av[ac -1], O_CREAT | O_RDWR | O_TRUNC, 0664);
	ft_checkfd_bonus(ppx, av[1]);
	if (access(av[1], R_OK) == -1)
	{
		close(ppx.fd0);
		perror("Error");
		exit(1);
	}
	ft_checkfd_bonus(ppx, av[1]);
	pipex_bonus(envp, av, ppx);
	return (0);
}
