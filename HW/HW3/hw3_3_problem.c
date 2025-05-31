#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <pthread.h>

#include "Console.h"

#define TRUE 1
#define FALSE 0

typedef struct {
	int sx, sy;
	int length;
	int delay;

	int screen_width;
} Bar;

void DrawBar(int sx, int sy, int len, char c);

int cont = TRUE;
void* ThreadFn(void *vparam);

int main()
{
	srand(time(NULL));

	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	clrscr();
	printf("Press ESC to finish.\n");

	// thread parameters (use this array as the arguments for the thread function)
	Bar bar[3] = {
		{ rand() % (screen_width - 5) + 1, screen_height / 4, 5, 50, screen_width },
		{ rand() % (screen_width - 5) + 1, screen_height / 2, 5, 50, screen_width },
		{ rand() % (screen_width - 5) + 1, screen_height * 3 / 4, 5, 50, screen_width }
	};

	pthread_t tid[3] = { 0 };

	// TO DO: create three threads using ThreadFn and bar[t]

	// wait for the ESC key
	while(1){
		if(getch() == 27)
			break;
		MySleep(10);
	};

	// terminate threads
	cont = FALSE;

	// TO DO: wait for the threads



	gotoxy(1, screen_height);
	printf("Bye!\n");

	return 0;
}

void DrawBar(int sx, int sy, int len, char c)
// DO NOT MODIFY THIS FUNCTION.
{
	LockDisplay();

	gotoxy(sx, sy);
	for(int i = 0; i < len; i++)
		putchar(c);

	UnlockDisplay();
}

void* ThreadFn(void *vparam)
// TO DO: complete this function by referring to hw3_3_ST.c
{
	Bar *bar = (Bar *)vparam;
	while(cont){
		// TO DO: write your code here




}

