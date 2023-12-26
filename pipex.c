/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:41:33 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/25 18:56:43 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
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

void	ft_cmmd_notfound(char *av1, char *av2, t_pipex ppx)
{
	close(ppx.fd0);
	close(ppx.fd1);
	ft_putstr_fd(av1, 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_putstr_fd(av2, 2);
	ft_putstr_fd(": command not found\n", 2);
	free(ppx.cmd1);
	free(ppx.cmd2);
	exit(127);
}

char	*ft_add(char **envp, char *ag)
{
	char	*cmd1;
	char	**str;
	char	**args;
	char	*tmp;
	int		i;

	i = 0;
	str = get_path(envp);
	args = ft_split(ag, ' ');
	if (!*str)
		return (NULL);
	while (str[i])
	{
		tmp = ft_strjoin(str[i], "/");
		cmd1 = ft_strjoin(tmp, args[0]);
		free(tmp);
		if (access(cmd1, X_OK) == 0)
			return (ft_free_str(args), ft_free_str(str), cmd1);
		free(cmd1);
		i++;
	}
	return (ft_free_str(args), ft_free_str(str), NULL);
}

void	pipex(char **envp, char **av, t_pipex ppx)
{
	int		i;
	int		j;

	i = 2;
	j = 1;
	while (j < ppx.ac)
	{
		ppx.cmd1 = ft_add(envp, av[i]);
		ppx.cmd2 = ft_add(envp, av[i + 1]);
		if (!ppx.cmd1 && !ppx.cmd2)
			ft_cmmd_notfound(av[i], av[i + 1], ppx);
		if (pipe(ppx.end) == -1)
			exit(EXIT_FAILURE);
		ppx.child1 = fork();
		if (ppx.child1 == 0)
			first_c(av[i], ppx, envp);
		else
			second_c(av[i + 1], envp, j, ppx);
		i++;
		j++;
	}
}

