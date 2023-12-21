/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:41:33 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/12/21 14:09:52 by braasantos       ###   ########.fr       */
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

char **get_path(char **envp)
{
	int i;
	char *str;
	char **newstr;

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

void ft_add(char **envp, char *ag)
{
	char *cmd1;
	char **str;
	char **args;
	char *tmp;

	str = get_path(envp);
	args = ft_split(ag, ' ');
	if (!*str)
		return;
	while (*str)
	{
		tmp = ft_strjoin(*str, "/");
		cmd1 = ft_strjoin(tmp, args[0]);
		execve(cmd1, args, envp);
		str++;
	}
}

/*
Checks the path on the envp and splits it based on the ":"
*/

void pipex(char **envp, char **av, int fdw, int fdr)
{
	int end[2];
	pid_t child;

	if (pipe(end) == -1)
		exit(1);
	child = fork();
	if (child < 0)
		exit(1);
	if (dup2(fdr, 0) < 0)
		exit(1);
	if (child == 0)
		ft_child(envp, av[2], end, fdr);
	else
		ft_parent(envp, av[3], fdw, end);
}

int main(int ac, char **av, char **envp)
{
	int fdw;
	int fdr;

	if (ac != 5)
		return (1);
	if (!av[1][0])
		return (0);
	if (!av[4][0])
		return (1);
	if (av[2][0] == '\0')
		return (0);
	fdr = open(av[1], O_RDONLY);
	fdw = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (access(av[1], R_OK) == -1)
	{
		close(fdr);
		perror("Error");
		exit(0);
	}
	if (fdr < 0 || fdw < 0)
	{
		perror("Error");
		close(fdw);
		close(fdr);
		exit(1);
	}
	pipex(envp, av, fdw, fdr);
	return (0);
}

// end[0] = read parent cmd2 fd0 é o stdin (fd0 ledo
// fd1 o output do cmd1 e outfile e o stdout)
// end[1] = write child cmd1 infile =stdin/input e o fd1 o stdo
// ut, escrever no fd1 o output do cmd1
