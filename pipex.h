/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:44:49 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/07/02 13:33:38 by bjorge-m         ###   ########.fr       */
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

void	pipex(t_pipex ppx, char **envp, char **av);
/*Utils*/

void	second_cmd(t_pipex ppx, char *av, char **envp, int j);
void	cmd_notfound(t_pipex ppx, char *av1, char *av2);
void	child2(t_pipex ppx, char **envp, char *av);
void	child1(t_pipex ppx, char **envp ,char *av);
void	st_cmd(t_pipex ppx, char *av, char **envp);
void	ft_close_and_exit(t_pipex ppx, char *av);
void	check_fds(t_pipex ppx, char **av);
void	check_file(t_pipex ppx, char *av);
void	last_cmd(t_pipex ppx);
void	wait_child(t_pipex ppx);
void	ft_free_str(char **str);
void	first_cmd(t_pipex ppx);
void	middle_cmd(t_pipex ppx);
void	free_cmd(t_pipex ppx);

#endif
