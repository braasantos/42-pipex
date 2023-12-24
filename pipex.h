/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:44:49 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/24 16:15:20 by braasantos       ###   ########.fr       */
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

/*BONUS Functions*/
void	pipex_bonus(char **envp, char **av, t_pipex ppx);
char	*ft_add_bonus(char **envp, char *ag);
char	**get_path_bonus(char **envp);
/*BONUS Utils*/
void	second_c_bonus(char *av, char **envp, int j, t_pipex ppx);
void	ft_cmmd_notfound_bonus(char *av1, char *av2, t_pipex ppx);
void	ft_child2_bonus(char **envp, char *av3, t_pipex ppx);
void	ft_child1_bonus(char **envp ,char *av2, t_pipex ppx);
void	first_c_bonus(char *av, t_pipex ppx, char **envp);
void	ft_close_and_exit1(t_pipex ppx, char *av2);
void	ft_close_and_exit2(t_pipex ppx, char *av3);
void	ft_checkfd_bonus(t_pipex ppx, char **av);
void	check_file(char **av, t_pipex ppx);
void	ft_closefinal_bonus(t_pipex ppx);
void	ft_free_cmd_bonus(t_pipex ppx);
void	ft_free_str_bonus(char **str);
void	ft_close1_bonus(t_pipex ppx);
void	ft_close2_bonus(t_pipex ppx);
#endif
