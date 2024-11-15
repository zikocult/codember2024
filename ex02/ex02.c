#include "./mylibft/include/get_next_line.h"
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

bool comprobación(char *gnl)
{
	int i = 0;
	char value = gnl[i];

	while (gnl[i] && gnl[i] != '\n') {
		while ((gnl[i] >= '0' && gnl[i] <= '9') && gnl[i] != '\n' && gnl[i]) {
			if (gnl[i] < value)
				return (false);
			value = gnl[i];
			i++;
		}
		while ((gnl[i] >='a' && gnl[i] <= 'z') && gnl[i] != '\n' && gnl[i]) {
			if ((gnl[i] < value) || (gnl[i] >= '0' && gnl[i] <= '9'))
				return (false);
		value = gnl[i];
		i++;
		}
	}

	return (true);
}

int main(void)
{
	int acierto = 0, total = 0;
	char *gnl;
	ssize_t fd1;
	char file1[1024] = "./proba.txt";

	fd1 = open(file1, O_RDONLY);
	if (fd1 == -1)
	{
		printf("Fail al abrir el fichero\n");
		return (1);
	}
	gnl = get_next_line(fd1);
	while (gnl) {
		if (comprobación(gnl))
			acierto++;
		free(gnl);
		gnl = get_next_line(fd1);
		total++;
	}
	close(fd1);
	printf("El número de aciertos es = %d\n", acierto);
	printf("El número de fallos ha sido = %d\n", total - acierto);
	printf("El número total es = %d\n", total);
	printf("submit %dtrue%dfalse\n", acierto, total - acierto);
	return EXIT_SUCCESS;
}
