/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:41:33 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/20 19:15:32 by bjorge-m         ###   ########.fr       */
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
		if (!strncmp(envp[i], "PATH=", 5))
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

void	ft_add(char **envp, char *ag)
{
	char	*cmd1;
	char	**str;
	char	**args;
	char	*tmp;

	str = get_path(envp);
	args = ft_split(ag, ' ');
	if (!*str)
		return ;
	while (*str)
	{
		tmp = ft_strjoin(*str, "/");
		cmd1 = ft_strjoin(tmp, args[0]);
		execve(cmd1, args, envp);
		str++;
	}
	perror("pipex: fizzbuzz");
	exit(127);
}

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
/*
Checks the path on the envp and splits it based on the ":"
*/

void	pipex(char **envp, char **av, int fdw, int fdr)
{
	int		end[2];
	pid_t	child;

	if (pipe(end) == -1)
		exit(1);
	child = fork();
	if (child < 0)
		return (perror("fork"));
	if (dup2(fdr, 0) < 0)
		exit(1);
	if (child == 0)
		ft_child(envp, av[2], end, fdr);
	else
		ft_parent(envp, av[3], fdw, end);
}

int	main(int ac, char **av, char **envp)
{
	int		fdw;
	int		fdr;
	if (ac != 5)
		return (0);
	if (av[1][0] == '\0' || av[2][0] == '\0' || 
			av[3][0] == '\0' || av[4][0] == '\0')
	{
		ft_printf("pipex: Argument invalid\n");
		return (0);
	}
	fdr = open(av[1], O_RDONLY);
	if(fdr == -1)
	{
		perror("pipex");
		exit(1);
	}
	fdw = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
	pipex(envp, av, fdw, fdr);
	return (0);
}

// end[0] = read parent cmd2 fd0 é o stdin (fd0 ledo 
// fd1 o output do cmd1 e outfile e o stdout)
// end[1] = write child cmd1 infile =stdin/input e o fd1 o stdo
// ut, escrever no fd1 o output do cmd1
