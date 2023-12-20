/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:31:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/20 19:31:45 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parent(char **envp, char *av3, int fdw, int *end)
{
	int		status;

	waitpid(-1, &status, 0);
	dup2(fdw, 1);
	dup2(end[0], 0);
	close(end[1]);
	close(end[0]);
	close(fdw);
	ft_add(envp, av3);
}

void	ft_child(char **envp, char *av2, int *end, int fdr)
{
	dup2(end[1], 1);
	close(end[0]);
	close(fdr);
	close(end[1]);
	ft_add(envp, av2);
	perror("pipex: fizzbuzz");
	exit(EXIT_FAILURE);
}
