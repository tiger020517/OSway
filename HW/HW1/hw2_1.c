#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int	ls(char *path, int recur, int level);

int	main(int argc, char *argv[])
{
	if (argc == 1)
		ls(".", 1, 0);
	else
		ls(argv[1], 1, 0);
	return (0);
}

int	ls(char *path, int recur, int level)
{
	char	*dot = ".";
	char	*slash = "/";
	char	newstr[1024] = {0};
	if (!path)
		path = dot;
	DIR	*dir = opendir(path);
	if (dir == NULL)
		return (printf("Open ERR!\n"), -1);
	printf("cur_dir = %s\n", path);
	struct dirent	*in;
	struct stat		stats;
	while ((in = readdir(dir)) != NULL)
	{
		strlcat(newstr, slash, 1023);
		strlcat(newstr, in->d_name, 1023);
		for (int idx = 0; idx < level; idx++)
			printf("    ");
		printf("%s\t\t\t%4u", in->d_name, (unsigned int)in->d_type); 
		stat(path, &stats);
		printf("  ");
		printf("%4u\t%ld\n", stats.st_uid, stats.st_size);
		newstr[0] = '\0';
	}
}
