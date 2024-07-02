/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:41:33 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/07/02 13:27:24 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/// @brief			Function to the the PATH variable
/// @param envp		The environment variables
/// @return			The PATH variable splitted in an array
static char	**get_path(char **envp)
{
	int		i;
	char	*str;
	char	**newstr;

	i = 0;
	str = NULL;
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
	{
		newstr = ft_split(str, ':');
		return (free(str), newstr);
	}
	return (NULL);
}


/// @brief			Function to add the command to the PATH to the command var
/// @param envp		The environment variables 
/// @param ag		The command to to check
/// @return			The Path to the command
static char	*ft_add(char **envp, char *ag)
{
	char	*cmd1;
	char	**str;
	char	**args;
	char	*tmp;
	int		i;

	i = 0;
	str = get_path(envp);
	if (!str || !*str)
		return (NULL);
	args = ft_split(ag, ' ');
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

/// @brief			Original function to create the pipes and child processes
/// 				and add the commands to the variables and execute them
/// @param envp		The environment variables
/// @param av		Array of Arguments received
/// @param ppx		The structure with the data
void	pipex(t_pipex ppx, char **envp, char **av)
{
	int	i;
	int	j;

	i = 2;
	j = 1;
	while (j < ppx.ac)
	{
		ppx.cmd1 = ft_add(envp, av[i]);
		ppx.cmd2 = ft_add(envp, av[i + 1]);
		if (!ppx.cmd1 && !ppx.cmd2)
			cmd_notfound(ppx, av[i], av[i + 1]);
		if (pipe(ppx.end) == -1)
		{
			free_cmd(ppx);
			exit(EXIT_FAILURE);
		}
		ppx.child1 = fork();
		if (ppx.child1 == 0)
			st_cmd(ppx, av[i], envp);
		else
			second_cmd(ppx, av[i + 1], envp, j);
		i++;
		j++;
	}
}

