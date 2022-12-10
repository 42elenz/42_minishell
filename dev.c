#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

char *create_name()
{
	int fd = open("/dev/random", O_RDONLY);
	char buf[10];
	char *str;
	int	i;

	while(1)
	{
		i = 0;
		read(fd, buf, 9);
		buf[9] = '\0';
		while (buf[i])
		{
			buf[i] = (buf[i] * buf[i]) % 25 + 'a';
			i++;
		}
		if (access(buf, F_OK) != 0)
			break ;
	}
	close(fd);
	return (buf);
}
