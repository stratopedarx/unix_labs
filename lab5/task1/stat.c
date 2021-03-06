#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	//char buf[] = "Lalala\nkakakaa\ndasdsad\n";
	char str[256] = {0};
	int fd1, fd2, size;
	struct stat st1;
	if (argc != 3)
	{
		perror("Args error!");
		return 1;
	}
	fd1 = open(argv[1], O_RDONLY);
	//write(fd1, buf, sizeof(buf));
	stat(argv[1], &st1);	// fill struct st1 the information about fd1
	if(!S_ISREG(st1.st_mode))
	{
		perror("File is not reular!");
		return 2;
	}
	fd2 = open (argv[2], O_CREAT | O_WRONLY, st1.st_mode);
	while((size = read(fd1, str, 5)) > 0)
		write(fd2, str, size);
	while(size = read(fd1, str, sizeof(str)))
		write(fd2, str, sizeof(str));

	//chmod(fd2, st1.st_mode);
	close(fd1);
	close(fd2);

	return 0;
}