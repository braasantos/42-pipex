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

/*Functions*/
char **get_path(char **envp);
void	ft_add(char **envp, char *ag);
void	pipex(char **envp, char **av, int fdw, int fdr);
/*Utils*/

#endif