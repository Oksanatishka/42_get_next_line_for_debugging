#include "get_next_line.h"
#include <stdio.h>

// find next line with \n in the end from buf
// and save it to the line argument
static	int	find_nl(int fd, char **buf, char **line)
{
	char		*new_line;
	printf("find_nl: ft_strchr before buf[fd] = %s\n\n", buf[fd]);
	// move buf until \n is found, when found - return pointer to that character
	new_line = ft_strchr(buf[fd], '\n');
	printf("find_nl: ft_strchr after buf[fd] = %s\n\n", buf[fd]);
	// if \n was found in the buf
	if (new_line)
	{
		// add end of line to it, now buf has end of line charkter after \n
		*new_line = '\0';
		printf("find_nl: ft_strsub: new_line = %d, buf[fd] = %d, new_line - buf[fd] = %d\n\n", (int)new_line, (int)buf[fd], (int)(new_line - buf[fd]));
		// cut string from buf starting from 0 to length of new_line
		// after that buf will be equal to our new line
		printf("find_nl: ft_strsub before: buf[fd] = %s\n\n", buf[fd]);
		*line = ft_strsub(buf[fd], 0, new_line - buf[fd]);
		printf("find_nl: *line = %s\n\n", *line);
		printf("find_nl: new_line = %s\n\n", new_line);
		printf("find_nl: new_line + 1 = %s\n\n", new_line + 1);
		printf("find_nl: ft_strdup before: buf[id] = %s\n\n", buf[fd]);
		// copy to buf everything what goes after \n + 1 (end of line)
		// basically buf will be equal to content in the file except first line
		buf[fd] = ft_strdup(new_line + 1);
		printf("find_nl: ft_strdup after: buf[id] = %s\n\n", buf[fd]);
		return (1);
	}
	// if \n was not found - save everything to line and return
	if (*buf[fd])
	{
		int length_of_buf = ft_strlen(buf[fd]);
		*line = ft_strnew(length_of_buf);
		ft_strcpy(*line, buf[fd]);
		buf[fd] = ft_memalloc(BUFF_SIZE + 1);
		return (1);
	}
	return (0);
}

// read from file by 32 characters to prevent memory issues
static	int	ft_read(int fd, char **line)
{
	char		*buf;
	int			i;
	// create new buf with 32 length
	buf = ft_strnew(BUFF_SIZE);
	// read from file by 32 characters until nothing is left in the file
	while ((i = read(fd, buf, BUFF_SIZE)) > 0)
	{
		printf("ft_read, i = %d\n\n", i);
		printf("ft_read, fd = %d\n\n", fd);
		// since fd is unique number (file descriptor) - we are going to allowcate for that file
		// only string by fd index
		// in case there are different files to read from - each file will be saving content to separate
		// string by index [fd]
		// if nothig found by fd index
		if (!line[fd])
		{
			// allocate memory with 32 sizw
			line[fd] = ft_strnew(ft_strlen(buf));
			// put first 32 bytes
			ft_strcpy(line[fd], buf);
			// printf("ft_read, ft_strcpy line[fd] = %s, buf = %s\n\n", line[fd], buf);
		}
		else
		{
			// printf("ft_read, else tmp = %s\n\n", tmp);
			line[fd] = ft_strjoin(line[fd], buf);
			// printf("ft_read, else line[fd] = %s, buf = %s\n\n", line[fd], buf);
		}
		ft_memset(buf, 0, BUFF_SIZE);
	}
	printf("ft_read end, buf = %s\n\n", buf);
	printf("ft_read end, i = %d\n\n", i);
	printf("ft_read end, line[fd] = %s\n\n", line[fd]);
	free(buf);
	return (i);
}

int			get_next_line(const int fd, char **line)
{
	printf("read result line[fd] 1: %s\n\n", line[fd]);
	// in case we need to open many files so we have enough indexes in buf
	// for example
	// buf[3] = content of file1
	// buf[4] = content of file2
	// buf[6] = content of file3
	static	char	*buf[FDS];
	int read_result = ft_read(fd, &buf[fd]);

	printf("read result: %d\n\n", read_result);
	printf("read result fd: %d\n\n", fd);
	printf("read result line[fd] 2: %s\n\n", line[fd]);
	printf("read result buf[fd] 2: %s\n\n", buf[fd]);
	if (!line || fd < 0 || BUFF_SIZE < 0 || read_result < 0 ||
fd > FDS)
		return (-1);
	if (find_nl(fd, &buf[fd], line) == 1)
		return (1);
	return (0);
}
