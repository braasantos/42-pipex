#include "pipex.h"

//pipe ou cano recebe uma array com 2 numeros end 0 e end 1 para que consigam
//comunicar end0 vai ler e o end 1 vai escrever cada um no seu propeio fd
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
	if (!envp[i])
		return (NULL);
	while (envp[i])
	{
		if (!strncmp(envp[i], "PATH=", 5))
			str = ft_strdup(envp[i]);
		i++;
	}
	newstr = ft_split(str, ':');
	return (newstr);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)ac;
	int i = 0;
	char **mlc = get_path(envp);
	while (mlc[i])
	{
		ft_printf("%s\n", mlc[i]);
		i++;
	}
	return (0);
}

	//end[0] = read parent cmd2 fd0 é o stdin (fd0 ledo fd1 o output do cmd1 e outfile e o stdout)
	//end[1] = write child cmd1 infile =stdin/input e o fd1 o stdout, escrever no fd1 o output do cmd1
