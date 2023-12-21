/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:44:49 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/21 20:36:12 by bjorge-m         ###   ########.fr       */
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
# include "ft_printf.h"

typedef struct s_pipex
{
	int			end;
	int			fdr;
	int			fdw;
	char		**commands;
}		t_pipex;

/*Functions*/
char	*ft_add(char **envp, char *ag);
char	**get_path(char **envp);
void	pipex(char **envp, char **av, int fdw, int fdr);
/*Utils*/
void	ft_child2(char **envp, char *cmd1, int fdw, int *end, char *av3);
void	ft_child1(char **envp, char *cmd1, int *end, int fdr, char *av2);
void	ft_free_str(char **str);
void	ft_checkfd(int fdr, char *av1, int fdw);
#endif
