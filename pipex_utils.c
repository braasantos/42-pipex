/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:31:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/23 21:22:27 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_cmd_og(char *cmd1, char *cmd2)
{
	waitpid(-1, NULL, 0);
	free(cmd1);
	free(cmd2);
}
void	ft_close2_og(t_pipex ppx)
{
	close(ppx.end[1]);
	dup2(ppx.fd1, 1);
	dup2(ppx.end[0], 0);
	close(ppx.end[0]);
}
void	ft_child2_og(char **envp, char *cmd1, char *av3, t_pipex ppx)
{
	char	**args;

	args = ft_split(av3, ' ');
	if (execve(cmd1, args, envp) == -1)
	{
		ft_free_str_og(args);
		free(cmd1);
		ft_close_and_exit1(ppx, av3);
		exit(127);
	}
}
void	ft_close1_og(t_pipex ppx)
{
	close(ppx.end[0]);
	dup2(ppx.fd0, 0);
	dup2(ppx.end[1], 1);
	close(ppx.end[1]);
}
void	ft_child1_og(char **envp, char *cmd1, char *av2, t_pipex ppx)
{
	char	**args;

	args = ft_split(av2, ' ');
	if (execve(cmd1, args, envp) == -1)
	{
		ft_free_str_og(args);
		free(cmd1);
		ft_close_and_exit1(ppx, av2);
		exit(127);
	}
}
