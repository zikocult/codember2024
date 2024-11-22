#include "../mylibft/include/libft.h"
#include "../mylibft/include/get_next_line.h"
#include "../mylibft/include/ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

int ft_evade(char *gnl)
{
	int moves = 0;
	char **command;
	int i = 0, lenght = 0;

	command = ft_split(gnl, ' ');
	while (command[lenght])
		lenght++;
	while (i < lenght && i >= 0)
	{
		if (command[i][0] == '-')
			i = i - (command[i][1] - 48);
		else if (command[i][0] == '0')
			command[i][0]++;
		else
			i = i + (command[i][0] - 48);
		moves++;
	}
	i = 0;
	while (command[i])
	{
		free (command[i]);
		i++;
	}
	free (command);
	return (moves);
}

int main (void)
{
	int total = 0, last = 0;
	char *gnl;
	ssize_t fd1;
	char file1[50] = "./trace.txt";

	fd1 = open(file1, O_RDONLY);
	if (fd1 == -1)
	{
		ft_printf("Fail al abrir el fichero\n");
		return (1);
	}
	gnl = get_next_line(fd1);
	while (gnl) {
		last = ft_evade(gnl);
		total = total + last;
		free(gnl);
		gnl = get_next_line(fd1);
	}
	ft_printf("submit %d-%d\n", total, last);
	close (fd1);
	return (0);
}
