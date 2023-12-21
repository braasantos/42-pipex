/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:44:49 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/21 23:29:14 by braasantos       ###   ########.fr       */
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

/*Functions*/
void	pipex(char **envp, char **av, int *fd);
char	*ft_add(char **envp, char *ag);
char	**get_path(char **envp);
/*Utils*/
void	ft_child2(char **envp, char *cmd1, char *av3);
void	ft_child1(char **envp, char *cmd1, char *av2);
void	ft_checkfd(int *fd, char *av1);
void	ft_free_cmd(char *cmd1, char *cmd2);
void	ft_close1(int *end, int *fd);
void	ft_close2(int *end, int *fd);
void	ft_free_str(char **str);
#endif
