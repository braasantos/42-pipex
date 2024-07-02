/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:31:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/07/02 13:28:55 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/// @brief			Closes the pipes and change the std if the command is on 
///					the beginning of the pipeline
/// @param ppx		The structure containing the file descriptors
void	first_cmd(t_pipex ppx)
{
	close(ppx.end[0]);
	dup2(ppx.fd0, STDIN_FILENO);
	dup2(ppx.end[1], STDOUT_FILENO);
	close(ppx.end[1]);
}
/// @brief			Closes the pipes and change the std if the command is on 
///					the middle of the pipeline
/// @param ppx		The structure containing the file descriptors
void	middle_cmd(t_pipex ppx)
{
	dup2(ppx.end[0], STDIN_FILENO);
	dup2(ppx.end[1], STDOUT_FILENO);
	close(ppx.end[1]);
}

/// @brief			Closes the pipes and change the std if the command is on 
///					the end of the pipeline
/// @param ppx		The structure containing the file descriptors
void	last_cmd(t_pipex ppx)
{
	dup2(ppx.end[0], STDIN_FILENO);
	close(ppx.end[0]);
	dup2(ppx.fd1, STDOUT_FILENO);
	close(ppx.end[1]);
}

/// @brief			Checks if the command is valid and execute them with execve
/// @param envp		The environment variables
/// @param av3		The command to execute
/// @param ppx		The structure containing the data
void	child2(t_pipex ppx, char **envp, char *av)
{
	char	**args;

	args = ft_split(av, ' ');
	if (ppx.cmd2 == NULL)
	{
		ft_free_str(args);
		free(ppx.cmd1);
		ft_close_and_exit(ppx, av);
		exit(2);
	}
	if (execve(ppx.cmd2, args, envp) == -1)
	{
		ft_free_str(args);
		free(ppx.cmd2);
		free(ppx.cmd1);
		ft_close_and_exit(ppx, av);
		exit(127);
	}
}

/// @brief			Execute the first command in the pipeline
/// @param envp		The environment variables
/// @param av		The command to execute
/// @param ppx		The structure containing the data
void	child1(t_pipex ppx, char **envp, char *av)
{
	char	**args;

	args = ft_split(av, ' ');
	if (ppx.cmd1 == NULL)
	{
		ft_free_str(args);
		free(ppx.cmd2);
		ft_close_and_exit(ppx, av);
		exit(2);
	}
	if (execve(ppx.cmd1, args, envp) == -1)
	{
		ft_free_str(args);
		free_cmd(ppx);
		ft_close_and_exit(ppx, av);
		exit(2);
	}
}
