#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <fcntl.h>

int	main(int ac, char **av)
{
	char	*line;
	int		fd;

	if (ac < 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		printf("while: %s\n", line);
		printf("\nwhile: end of line\n\n");
		free(line);
	}

	close(fd);
	return (0);
}
