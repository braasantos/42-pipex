/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:31:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/21 20:33:59 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_str(char **str)
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

void	ft_child2(char **envp, char *cmd1, int fdw, int *end, char *av3)
{
	char	**args;

	args = ft_split(av3, ' ');
	close(end[1]);
	dup2(fdw, 1);
	dup2(end[0], 0);
	close(end[0]);
	if (execve(cmd1, args, envp) == -1)
	{
		ft_free_str(args);
		exit(127);
	}
}

void	ft_child1(char **envp, char *cmd1, int *end, int fdr, char *av2)
{
	char	**args;

	args = ft_split(av2, ' ');
	close(end[0]);
	dup2(fdr, 0);
	dup2(end[1], 1);
	close(end[1]);
	if (execve(cmd1, args, envp) == -1)
	{
		ft_free_str(args);
		exit(2);
	}
}
