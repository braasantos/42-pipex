/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:44:49 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/20 22:03:39 by braasantos       ###   ########.fr       */
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
void	ft_add(char **envp, char *ag);
char	**get_path(char **envp);
void	pipex(char **envp, char **av, int fdw, int fdr);
/*Utils*/
void	ft_parent(char **envp, char *av3, int fdw, int *end);
void	ft_child(char **envp, char *av2, int *end, int fdr);
#endif
