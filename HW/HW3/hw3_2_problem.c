#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <unistd.h>
#include <wait.h>
#include <errno.h>

#define MAX_LEN 512
#define MAX_PATH 256
#define MAX_ARG 256

#define TRUE 1
#define FALSE 0

#define	DEBUG			// commenting out this line disables debugging messages

int SplitArgs(char *input, char *args[], int max_arg);

int main()
{
	printf("Welcome to my_shell1!\n");

	char prompt[32] = "my_shell $";
	char input[MAX_LEN] = "";
	char *args[MAX_ARG] = { NULL };

	while(1){
		printf("%s ", prompt);
		fgets(input, MAX_LEN, stdin);
		int len = strlen(input) - 1;
		input[len] = 0;

#ifdef	DEBUG
		printf("input command = \"%s\" (len = %d)\n", input, len);
#endif	//	DEBUG

		int no_arg = SplitArgs(input, args, MAX_ARG);
	
#ifdef	DEBUG
		printf("no_arg = %d\n", no_arg);
		for(int i = 0; i < no_arg; i++)
			printf("args[%d] = \"%s\"\n", i, args[i]);
		printf("args[%d] = %p\n", no_arg, args[no_arg]);
#endif	//	DEBUG

		if(no_arg == 0)
			continue;

		int wait_for_child = TRUE;
		// TO DO: if the last argument is "&", remove it and set wait_for_child to zero

		// TO DO: if the command is "exit", break the loop

		// TO DO: if the command is "cd", change directory by calling chdir()
			// on failure, display an error message using strerror(errno)

		// TO DO: otherwise, run the command using fork() and execvp()
			// if wait_for_child is one, the parent should wait for the child
			// on failure, display error message using strerror(errono) and terminate the child
	}

	printf("Bye!\n");

	return 0;
}

int SplitArgs(char *input, char *args[], int max_arg)
// Bonus Problem (optional): extend this function to handle quoted arguments
//		- handle quoted (" or ') arguments (e.g., echo "Wecome to HGU!")
//		- handle escape character '\\' (e.g., echo Welcome\ to\ HGU!)
{
	int len = strlen(input);
	int no_arg = 0;

	for(int i = 0; i < len; i++){
		while(isspace(input[i]))
			i++;

		if(input[i] == 0)
			break;

		args[no_arg++] = &input[i];

		for(; i < len && !isspace(input[i]); i++);

		input[i] = 0;

		if(no_arg >= max_arg - 1)		// -1 is for the NULL pointer
			break;
	}

	args[no_arg] = NULL;

	return no_arg;
}

