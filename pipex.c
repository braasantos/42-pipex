/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:41:33 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/22 22:25:28 by braasantos       ###   ########.fr       */
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
	ft_free_str(args);
	ft_free_str(str);
	return (NULL);
}
/*
Checks the path on the envp and splits it based on the ":"
*/

void	pipex(char **envp, char **av, int *fd)
{
	int		end[2];
	pid_t	child;
	pid_t	child2;
	char	*cmd1;
	char	*cmd2;

	if (pipe(end) == -1)
		exit(1);
	child = fork();
	if (child == 0)
	{
		ft_close1(end, fd);
		ft_child1(envp, cmd1 = ft_add(envp, av[2]), av[2]);
	}
	else
	{
		child2 = fork();
		if (child2 == 0)
		{
			ft_close2(end, fd);
			ft_child2(envp, cmd2 = ft_add(envp, av[3]), av[3]);
		}
		else
			ft_free_cmd(cmd1 = ft_add(envp, av[2]), cmd2 = ft_add(envp, av[3]));
	}
}

void	ft_checkfd(int *fd, char *av1)
{
	if (fd[0] == -1)
	{
		av1 = ft_strjoin(av1, ": ");
		ft_putstr_fd(av1, 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free(av1);
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	if (fd[1] < 0)
	{
		perror("Error");
		close(fd[1]);
		close(fd[0]);
		exit(1);
	}
}
int	main(int ac, char **av, char **envp)
{
	int		fd[2];

	if (ac != 5 || !av[4][0])
		return (1);
	if (av[2][0] == '\0' || !av[1][0])
		return (0);
	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
	ft_checkfd(fd, av[1]);
	if (access(av[1], R_OK) == -1)
	{
		close(fd[0]);
		perror("Error");
		exit(0);
	}
	ft_checkfd(fd, av[1]);
	pipex(envp, av, fd);
	return (0);
}
// end[0] = read parent cmd2 fd0 é o stdin (fd0 ledo
// fd1 o output do cmd1 e outfile e o stdout)
// end[1] = write child cmd1 infile =stdin/input e o fd1 o stdo
// ut, escrever no fd1 o output do cmd1
