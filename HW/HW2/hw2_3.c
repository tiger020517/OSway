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
	char	in[1024] = {0};
	char	*NULLSTR = "NULL";
	printf("Welcome to my_shell0. This shell suports cd, ls, recur_ls, md, rd, exit commands.\n");
	printf(" - cd <dir>: change directory\n");
	printf(" - ls [<dir>]: list the files and subdirecotries of the specifed directory\n");
	printf("\tif <dir> is omitted, list the current directory\n");
	printf(" - cur_ls [<dir>]: list the files and subdirectories of the specified directory in a recursive way\n\tif <dir> is omitted, list the current directory");
	printf(" - md <dir>: make a new directory\n");
	printf(" - rd <dir>: remove a director\n");
	printf(" - exit: print \"Bye!\" and terminate\n");
	while (1)
	{
		char	*token;
		char	*args[3];
		int		count = 0;
		printf("my_shell0 $ ");
		fgets(in, 1023, stdin);
		in[strcspn(in, "\n")] = '\0';
		printf("input command = %s\n", in);
		token = strtok(in, " ");
		while (token != NULL && count < 3)
		{
			args[count++] = token;
			token = strtok(NULL, " ");
		}
		if (count == 0)
		{
			args[0] = NULLSTR;
			args[1] = NULLSTR;
		}
		else if (count == 1)
			args[1] = NULLSTR;
		printf("cmd = ([%s], [%s])\n", args[0], args[1]);
		if (!strcmp(args[0], "exit"))
			return (printf("Bye\n"), 1);
		else if (!strcmp(args[0], "md") && count == 2)
			mkdir(args[1], 0777);
		else if (!strcmp(args[0], "rd") && count == 2)
			rmdir(args[1]);
		else if (!strcmp(args[0], "cd") && count == 2)
			chdir(args[1]);
		else if (!strcmp(args[0], "ls"))
		{
			if (count == 2)
				ls(args[1], 0, 0);
			else
				ls(".", 0, 0);
		}
		else if (!strcmp(args[0], "cur_ls"))
		{
			if (count == 2)
				ls(args[1], 1, 0);
			else
				ls(".", 1, 0);
		}
		else
			printf("Unknown command!\n");
	}
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
		strlcat(newstr, path, 1023);
		strlcat(newstr, slash, 1023);
		strlcat(newstr, in->d_name, 1023);
		for (int idx = 0; idx < level; idx++)
			printf("    ");
		printf("%s\t\t\t%4u", in->d_name, (unsigned int)in->d_type); 
		stat(newstr, &stats);
		printf("  ");
		printf("%4u\t%ld\n", stats.st_uid, stats.st_size);
		if (recur && in->d_type == DT_DIR && !(!strcmp(in->d_name, ".") || !strcmp(in->d_name, "..")))
			ls(newstr, recur, level + 1);
		newstr[0] = '\0';
	}
	closedir(dir);
	return (0);
}
