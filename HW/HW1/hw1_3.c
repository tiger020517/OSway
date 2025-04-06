/*
	
	1. Write a text line from the user.
	2. Retrieve all words from the input text.
	   (a word is a sequence of non-space characters separated by whitespace characters.)
		- Mark the start and end of each word by '[' and ']' in the next line.
		- Store all words in an array of structures 'words'.
	3. Display all words in the array 'words'.

	ex)
			input a text: Welcome to HGU!   Nice to see you!			// input text
			              [      ][ ][   ]  [   ][ ][  ][   ]			// start and end indices of each words

			words[0] = (0, 7, Welcome)
            words[1] = (8, 10, to)
            words[2] = (11, 15, HGU!)
            words[3] = (18, 22, Nice)
            words[4] = (23, 25, to)
            words[5] = (26, 29, see)
            words[6] = (30, 34, you!)


	Use the isspace() function to decide whether a character is whitespace or not.

	Compile command: gcc hw1_3.c
	
	Execution command: ./a.out

*/
/*
	Comments from 승주
		- Line 107 통일성을 유지 할 수 있었지만, 1로 고정된 값을 굳이 계산 할 필요 없다.
	
	Commnets from 철호
		- Line 148 Line start에 공백이 들어갔을때의 상황을 고려해보는게 좋을 것 같다.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_TEXT 256
#define MAX_LEN 128
#define SIZE 512

typedef struct {
	int start, end;			// the start and end indices of the word
	char substr[MAX_LEN];	// substring (word)
} Substring;

int	word_start(char	text[MAX_TEXT], int idx);
int	word_end(char text[MAX_TEXT], int idx);

Substring words[SIZE];	 	// array of structures to store words
int no_word = 0;			// the number of words

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
	int		wlen;	//word len

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
	idx = -1;
	sidx = 0;
	while (*(++idx + text))
	{
		if (word_start(text, idx) && word_end(text, idx))
		{
			words[sidx].start = idx;
			words[sidx].end = idx;
			wlen = words[sidx].end - words[sidx].start + 1;
			for (int i = 0; i < wlen; i++)
				words[sidx].substr[i] = text[words[sidx].start + i];
			words[sidx].substr[wlen] = 0;
			sidx++;
		}
		else if (word_start(text, idx))
			words[sidx].start = idx;
		else if (word_end(text, idx))
		{
			words[sidx].end = idx;
			wlen = words[sidx].end - words[sidx].start + 1;
			for (int i = 0; i < wlen; i++)
				words[sidx].substr[i] = text[words[sidx].start + i];
			words[sidx].substr[wlen] = 0;
			sidx++;
		}
	}
	no_word = wc;





	int	i;
	// DO NOT modify the following four lines
	putchar('\n');
	putchar('\n');
	for(i = 0; i < no_word; i++)
		printf("words[%d] = (%d, %d, %s)\n", i, words[i].start, words[i].end, words[i].substr);

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