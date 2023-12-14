#include "pipex.h"

int main(int ac, char **av)
{
	(void)av;
	int end[2];
	int id;
	char *buff = (char *)malloc(sizeof(char));

	//end[0] = read parent cmd2 fd0 é o stdin (fd0 ledo fd1 o output do cmd1 e outfile e o stdout)
	//end[1] = write child cmd1 infile =stdin/input e o fd1 o stdout, escrever no fd1 o output do cmd1

	if (ac != 5)
		return (0);
	pipe(end);
	if (end == -1)
		return (1);
	id = fork();
	if (id < 0)
		return (perror("error boi"));
	if (id == 0)
	{
		close(end[1]);
		read(end[0], buff, sizeof(int));
		close(end[0]);
	}
	else
	{
		close(end[0]);
		write(end[0], &buff, sizeof(int));
		close(end[1]);
	}
	return (0);
}
