/*
	
	1. Write a text line from the user.
	2. Retrieve the start and end indices of all words from the input text.
	   (a word is a sequence of non-space characters separated by whitespace characters.)
		- Mark the start and end of each word by '[' and ']' in the next line

	ex)
			input a text: Welcome to HGU!   Nice to see you!			// input text
			              [      ][ ][   ]  [   ][ ][  ][   ]			// start and end indices of each words

	Use the isspace() function to decide whether a character is whitespace or not.

	Compile command: gcc hw1_2.c
	
	Execution command: ./a.out

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_TEXT 256

int	word_end(char str[MAX_TEXT], int idx);
int	word_start(char	str[MAX_TEXT], int idx);

int main()
{
	char *prompt = "input a text: ";
	int prompt_len = strlen(prompt);

	// read a text line
	char text[MAX_TEXT] = "";
	printf("%s", prompt);
	fgets(text, MAX_TEXT, stdin);
	int len = strlen(text) - 1;
	text[len] = 0;

	// TO DO: print '[' below the start of each word
	//        print ']' below the space character just after each word
	//		  store each word in the substring array
	//		  - start, end: the start and end indices of the word
	//		  - substr: the word

	int		idx;	//world count
	int		wc;		//index
	int		sidx;	//substr idx
	int		wstart;	//word start
	int		wlen;	//word len
	char	**substr;

	printf("              ");
	idx = -1;
	wc = 0;
	while (*(++idx + text))
	{
		if (word_start(text, idx) && word_end(text, idx))
		{
			printf("[");
			printf("]");
			wc++;
		}
		else if (word_start(text, idx))
			printf("[");
		else if (word_end(text, idx))
		{
			printf("]");
			wc++;
		}
		else
			printf(" ");
	}

	substr = (char **)malloc(sizeof(char *) * wc + 1);
	substr[wc] = NULL;
	idx = -1;
	sidx = 0;
	while (*(++idx + text))
	{
		if (word_start(text, idx) && word_end(text, idx))
		{
			wstart = idx;
			wlen = idx - wstart + 1;
			substr[sidx] = (char *)malloc(wlen + 1);
			for (int i = 0; i < wlen; i++)
				substr[sidx][i] = text[wstart + i];
			substr[sidx][wlen] = 0;
			sidx++;
		}
		else if (word_start(text, idx))
			wstart = idx;
		else if (word_end(text, idx))
		{
			wlen = idx - wstart + 1;
			substr[sidx] = (char *)malloc(wlen + 1);
			for (int i = 0; i < wlen; i++)
				substr[sidx][i] = text[wstart + i];
			substr[sidx][wlen] = 0;
			sidx++;
		}
	}

	/*printf("\n");
	for (int i = 0; substr[i]; i++)
		printf("%s\n", substr[i]);*/

	putchar('\n');
	printf("Bye!\n");

	return 0;
}

int	word_start(char	text[MAX_TEXT], int idx)
{
	if (idx == 0 || (text[idx] && isspace(text[idx - 1])))
		return (1);
	else
		return (0);
}
int	word_end(char text[MAX_TEXT], int idx)
{
	if (!isspace(text[idx]) && (!text[idx + 1] || isspace(text[idx + 1])))
		return (1);
	else
		return (0);
}