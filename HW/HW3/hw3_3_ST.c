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

int main()
{
	srand(time(NULL));

	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	clrscr();
	printf("Press ESC to finish.\n");

	Bar bar = { rand() % (screen_width - 5) + 1, screen_height / 2, 5, 50, screen_width };
	
	while(1){
		if(kbhit() && getch() == 27)		// break on ESC (not necessary for multi-threaded version)
			break;

		DrawBar(bar.sx, bar.sy, bar.length, ' ');

		bar.sx += 2;

		if(bar.sx + bar.length >= screen_width)
			bar.sx = 1;

		DrawBar(bar.sx, bar.sy, bar.length, '=');
		fflush(stdout);

		MySleep(bar.delay);
	}

	gotoxy(1, screen_height);
	printf("Bye!\n");

	return 0;
}

void DrawBar(int sx, int sy, int len, char c)
// DO NOT MODIFY THIS FUNCTION
{
	LockDisplay();

	gotoxy(sx, sy);
	for(int i = 0; i < len; i++)
		putchar(c);

	UnlockDisplay();
}

