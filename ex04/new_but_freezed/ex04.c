#include "../mylibft/include/libft.h"
#include "../mylibft/include/ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

int	ft_count_file(char *file)
{
	int		counter;
	char	caracter;
	int		fd;

	counter = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Dict Error\n");
		return (0);
	}
	while (read(fd, &caracter, 1) == 1)
		counter++;
	close(fd);
	return (counter);
}

char	*ft_load_file(char *file, int count)
{
	int		fd;
	ssize_t	nr_bytes;
	char	*buff;

	buff = (char *)malloc(sizeof(char) * count + 1);
	if (!buff)
		return (0);
	fd = open(file, O_RDONLY);
	nr_bytes = read(fd, buff, count);
	if (fd == -1)
		return (0);
	if (nr_bytes == 0)
	{
		ft_printf("Dict Error\n");
		return (0);
	}
	close(fd);
	return (buff);
}

int main(void)
{
	char file1[50] = "./network.txt";
	char *buff;
	char **split;
	
	buff = ft_load_file(file1, ft_count_file(file1));
	split = ft_split(buff, ' ');
	free(buff);
	int i = 0;
	while (split[i]) {
		ft_printf("%s\n", split[i]);
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}
