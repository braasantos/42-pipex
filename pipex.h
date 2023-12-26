/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:44:49 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/25 18:49:45 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"
# include "printf.h"

typedef struct	spipex
{
	pid_t	child1;
	pid_t	child2;
	int		fd0;
	int		fd1;
	int		end[2];
	char	*cmd1;
	char	*cmd2;
	int		ac;
}		t_pipex;

/*Functions*/
void	pipex(char **envp, char **av, t_pipex ppx);
char	*ft_add(char **envp, char *ag);
char	**get_path(char **envp);
/*Utils*/
void	second_c(char *av, char **envp, int j, t_pipex ppx);
void	ft_cmmd_notfound(char *av1, char *av2, t_pipex ppx);
void	ft_child2(char **envp, char *av3, t_pipex ppx);
void	ft_child1(char **envp ,char *av2, t_pipex ppx);
void	first_c(char *av, t_pipex ppx, char **envp);
void	ft_close_and_exit1(t_pipex ppx, char *av2);
void	ft_close_and_exit2(t_pipex ppx, char *av3);
void	ft_checkfd(t_pipex ppx, char **av);
void	check_file(char **av, t_pipex ppx);
void	ft_closefinal(t_pipex ppx);
void	ft_free_cmd(t_pipex ppx);
void	ft_free_str(char **str);
void	ft_close1(t_pipex ppx);
void	ft_close2(t_pipex ppx);

#endif
