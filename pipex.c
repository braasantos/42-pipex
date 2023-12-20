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
	char *cmd1;
	char **str;
	char **args;
	char *tmp;

	str = get_path(envp);
	args = ft_split(ag, ' ');
	if (!*str)
		return ;
	while (*str)
	{
		tmp = ft_strjoin(*str, "/");
		cmd1 = ft_strjoin(tmp, args[0]);
		execve(cmd1, args, envp);
		free(tmp);
		free(cmd1);
		str++;
	}
	free(args);
}
/*
Checks the path on the envp and splits it based on the ":"
*/
void	pipex(char **envp, char **av, int fdw, int fdr)
{
	int		end[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (pipe(end) == -1)
		exit(1);
	child1 = fork();
	if (child1 < 0)
		return (perror("fork"));
	if (child1 == 0)
	{
		close(end[0]);
		dup2(end[1], 1);
		close(end[1]);
		ft_add(envp, av[2]);
		perror("execve");
		exit(1);
	}
	child2 = fork();
	if (child2 < 0)
		return (perror("fork"));
	if (child2 == 0)
	{
		close(end[1]);
		dup2(end[0], 0);
		close(end[0]);
		dup2(fdw, 1);
		close(fdw);
		ft_add(envp, av[3]);
		perror("execve");
		exit(1);
	}
	close(end[0]);
	close(end[1]);
	close(fdr);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}
int main(int ac, char **av, char **envp)
{
	int fdw;
	int fdr;
	if (ac != 5)
		return (0);
	fdr = open(av[1], O_RDONLY);
	fdw = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
	pipex(envp, av, fdw, fdr);
	return (0);
}

// end[0] = read parent cmd2 fd0 é o stdin (fd0 ledo fd1 o output do cmd1 e outfile e o stdout)
// end[1] = write child cmd1 infile =stdin/input e o fd1 o stdout, escrever no fd1 o output do cmd1
