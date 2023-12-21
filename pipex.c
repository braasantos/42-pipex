/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:41:33 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/21 20:32:26 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// pipe ou cano recebe uma array com 2 numeros end 0 e end 1 para que consigam
// comunicar end0 vai ler e o end 1 vai escrever cada um no seu propeio fd
/*fork vai dividir os processos em 2
o child fica com id de 0 o pai com um n posi e -1 em caso de erro
*/
/*dup2 ajuda a redirecionar ou substituir o fd default por outro
 */

char	**get_path(char **envp)
{
	int		i;
	char	*str;
	char	**newstr;

	i = 0;
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
		newstr = ft_split(str, ':');
	free(str);
	return (newstr);
}
/*
Add the command1 recieved a join with the path
*/

char	*ft_add(char **envp, char *ag)
{
	char	*cmd1;
	char	**str;
	char	**args;
	char	*tmp;
	int		i;

	i = 0;
	str = get_path(envp);
	args = ft_split(ag, ' ');
	if (!*str)
		return (NULL);
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
/*
Checks the path on the envp and splits it based on the ":"
*/

void	pipex(char **envp, char **av, int fdw, int fdr)
{
	int		end[2];
	pid_t	child;
	pid_t	child2;
	char	*cmd1;
	char	*cmd2;

	cmd1 = ft_add(envp, av[2]);
	cmd2 = ft_add(envp, av[3]);
	if (pipe(end) == -1)
		exit(1);
	child = fork();
	if (child == 0)
		ft_child1(envp, cmd1, end, fdr, av[2]);
	else
	{
		child2 = fork();
		if (child2 == 0)
			ft_child2(envp, cmd2, fdw, end, av[3]);
		else 
		{
			waitpid(-1, NULL, 0);
			free(cmd1);
			free(cmd2);
		}
	}
}

void	ft_checkfd(int fdr, char *av1, int fdw)
{
	if (fdr == -1)
	{
		ft_putstr_fd(av1, 2);
		ft_putstr_fd(strerror(errno), 2);
		exit(0);
	}
	if (fdr < 0 || fdw < 0)
	{
		perror("Error");
		close(fdw);
		close(fdr);
		exit(1);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		fdw;
	int		fdr;

	if (ac != 5 || !av[4][0])
		return (1);
	if (av[2][0] == '\0' || !av[1][0])
		return (0);
	fdr = open(av[1], O_RDONLY);
	fdw = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
	ft_checkfd(fdr, av[1], fdw);
	if (access(av[1], R_OK) == -1)
	{
		close(fdr);
		perror("Error");
		exit(0);
	}
	ft_checkfd(fdr, av[1], fdw);
	pipex(envp, av, fdw, fdr);
	return (0);
}
// end[0] = read parent cmd2 fd0 é o stdin (fd0 ledo
// fd1 o output do cmd1 e outfile e o stdout)
// end[1] = write child cmd1 infile =stdin/input e o fd1 o stdo
// ut, escrever no fd1 o output do cmd1
