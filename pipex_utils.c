/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:31:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/25 18:51:44 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close2(t_pipex ppx)
{
	dup2(ppx.end[0], STDIN_FILENO);
	dup2(ppx.end[1], STDOUT_FILENO);
	close(ppx.end[1]);
}

void	ft_closefinal(t_pipex ppx)
{
	dup2(ppx.end[0], STDIN_FILENO);
	close(ppx.end[0]);
	dup2(ppx.fd1, STDOUT_FILENO);
	close(ppx.end[1]);
}

void	ft_child2(char **envp, char *av3, t_pipex ppx)
{
	char	**args;

	args = ft_split(av3, ' ');
	if (ppx.cmd2 == NULL)
	{
		ft_free_str(args);
		free(ppx.cmd1);
		free(ppx.cmd2);
		ft_close_and_exit1(ppx, av3);
		exit(2);
	}
	if (execve(ppx.cmd2, args, envp) == -1)
	{
		ft_free_str(args);
		free(ppx.cmd2);
		free(ppx.cmd1);
		ft_close_and_exit2(ppx, av3);
		exit(127);
	}
}

void	ft_close1(t_pipex ppx)
{
	close(ppx.end[0]);
	dup2(ppx.fd0, STDIN_FILENO);
	dup2(ppx.end[1], STDOUT_FILENO);
	close(ppx.end[1]);
}

void	ft_child1(char **envp, char *av2, t_pipex ppx)
{
	char	**args;

	args = ft_split(av2, ' ');
	if (ppx.cmd1 == NULL)
	{
		ft_free_str(args);
		free(ppx.cmd1);
		free(ppx.cmd2);
		ft_close_and_exit1(ppx, av2);
		exit(2);
	}
	if (execve(ppx.cmd1, args, envp) == -1)
	{
		ft_free_str(args);
		free(ppx.cmd1);
		free(ppx.cmd2);
		ft_close_and_exit1(ppx, av2);
		exit(2);
	}
}
