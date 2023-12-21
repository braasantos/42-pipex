/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:31:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/21 23:39:54 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_free_cmd(char *cmd1, char *cmd2)
{
	waitpid(-1, NULL, 0);
	free(cmd1);
	free(cmd2);
}
void	ft_close2(int *end, int* fd)
{
	close(end[1]);
	dup2(fd[1], 1);
	dup2(end[0], 0);
	close(end[0]);
}
void	ft_child2(char **envp, char *cmd1, char *av3)
{
	char	**args;

	args = ft_split(av3, ' ');
	if (execve(cmd1, args, envp) == -1)
	{
		ft_free_str(args);
		exit(127);
	}
}
void	ft_close1(int *end, int *fd)
{
	close(end[0]);
	dup2(fd[0], 0);
	dup2(end[1], 1);
	close(end[1]);
}
void	ft_child1(char **envp, char *cmd1, char *av2)
{
	char	**args;

	args = ft_split(av2, ' ');
	if (execve(cmd1, args, envp) == -1)
	{
		ft_free_str(args);
		exit(2);
	}
}
