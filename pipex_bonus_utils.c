/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:31:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/23 12:43:58 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close2_bonus(t_pipex ppx)
{
	dup2(ppx.end[0], STDIN_FILENO);
	dup2(ppx.end[1], STDOUT_FILENO);
	close(ppx.end[1]);
}
void	ft_closefinal_bonus(t_pipex ppx)
{
	dup2(ppx.end[0], STDIN_FILENO);
	close(ppx.end[0]);
	dup2(ppx.fd1, STDOUT_FILENO);
	close(ppx.end[1]);
}
void	ft_child2_bonus(char **envp, char *av3, t_pipex ppx)
{
	char	**args;

	args = ft_split(av3, ' ');
	if (execve(ppx.cmd2, args, envp) == -1)
	{
		ft_free_str_bonus(args);
		exit(1);
	}
}
void	ft_close1_bonus(t_pipex ppx)
{
	close(ppx.end[0]);
	dup2(ppx.fd0, STDIN_FILENO);
	dup2(ppx.end[1], STDOUT_FILENO);
	close(ppx.end[1]);
}
void	ft_child1_bonus(char **envp, char *av2, t_pipex ppx)
{
	char	**args;

	args = ft_split(av2, ' ');
	if (execve(ppx.cmd1, args, envp) == -1)
	{
		ft_free_str_bonus(args);
		exit(2);
	}
}
