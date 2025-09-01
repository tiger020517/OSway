/*

	compilation:
		gcc hw5_2.c Console.c -o hw5_2

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <pthread.h>

// TO DO: include header files to use semaphore
#include <semaphore.h>

#include "Console.h"

#define MAX(x, y) ((x) >= (y) ? (x) : (y))
#define MIN(x, y) ((x) <= (y) ? (x) : (y))
#define ABS(x) ((x) >= 0 ? (x) : -(x))

#define TRUE 1
#define FALSE 0

#define ESC 27

typedef struct {
	int left, top, right, bottom;
} Rect;

typedef struct {
	char c;

	int sx, sy;
	int ex, ey;

	int len;
	int update_freq;

	Rect critical_region;
} MovingChar;


int screen_width = 0;
int screen_height = 0;

int cont = TRUE;


// TO DO: declare a semaphore globally
sem_t sem;

void* AnimateChar(void *vparam);
void InitChar(int left, int top, int right, int bottom, MovingChar *mc);
void GetBoundaryPoint(int left, int top, int right, int bottom, int *px, int *py);
int PointInRect(Rect *r, int x, int y);	// if (x, y) is in rectangle r, returns TRUE, otherwise returns FALSE

int main(int argc, char *argv[])
{
	srand(time(NULL));

	clrscr();

	screen_width = getWindowWidth();
	screen_height = getWindowHeight() - 3;

	printf("screen size = %d x %d\n", screen_width, screen_height);
	fflush(stdout);

	// TO DO: initialize unnamed semaphore
	//		  on failure, display an error message
	if (sem_init(&sem, 0, 3))
	{
		perror("Semaphore Failed");
		exit(1);
	}

	while(1){
		if(kbhit() && getch() == ESC)
			break;

		pthread_t tid = 0;
		pthread_create(&tid, NULL, AnimateChar, NULL);

		gotoxy(screen_width, screen_height);
		fflush(stdout);

		MySleep(100);
	}

	cont = FALSE;

	// TO DO: destroy the unnamed semaphore
	sem_destroy(&sem);


	gotoxy(1, screen_height);
	printf("Bye!\n");

	return 0;
}


void InitChar(int left, int top, int right, int bottom, MovingChar *mc)
{
	int p = rand() % (26 * 2 + 10);

	if(p < 26)
		mc->c = 'a' + p;
	else if(p < 52)
		mc->c = 'A' + (p - 26);
	else
		mc->c = '0' + (p - 52);

	GetBoundaryPoint(left, top, right, bottom, &mc->sx, &mc->sy);
	mc->ex = right - (mc->sx - left);
	mc->ey = bottom - (mc->sy - top);

	mc->len = MAX(ABS(right - left), ABS(bottom - top));

	mc->update_freq = 30;		// move character every 30th msec

	// set the coordinates of critical region
	mc->critical_region.left = screen_width * 3 / 8;
	mc->critical_region.top = screen_height * 3 / 8;
	
	mc->critical_region.right = screen_width * 5 / 8;
	mc->critical_region.bottom = screen_height * 5 / 8;
}

void GetBoundaryPoint(int left, int top, int right, int bottom, int *px, int *py)
{
	int width = right - left + 1;
	int height = bottom - top + 1;

	int circumference = (width + height) * 2;
	int p = rand() % circumference;

	if(p < width){
		*px = left + p;
		*py = top;
	} else if(p < width + height){
		p -= width;
		*px = right;
		*py = top + p;
	} else if(p < width + height + width){
		p -= width + height;
		*px = left + p;
		*py = bottom;
	} else {
		p -= width + height + width;
		*px = left;
		*py = left + p;
	}
}

void* AnimateChar(void *vparam)
{
	MovingChar mc = { 0 };
	InitChar(1, 1, screen_width, screen_height, &mc);

	int x = mc.sx;
	int y = mc.sy;

	int in_cr0 = FALSE;	

	int sval = 0;

	for(int t = 0; cont && t <= mc.len; t++){
		int prevx = x;
		int prevy = y;

		x = ((mc.len - t) * mc.sx + t * mc.ex + mc.len / 2) / mc.len;
		y = ((mc.len - t) * mc.sy + t * mc.ey + mc.len / 2) / mc.len;

		int in_cr = PointInRect(&mc.critical_region, x, y);

		// TO DO: when the character enters the critical region, call sem_wait()
		// hint: use in_cr0 and in_cr
		if (in_cr && !in_cr0)
			sem_wait(&sem);


		// TO DO: when the character leaves the critical region, call sem_post()
		// hint: use in_cr0 and in_cr
		if (!in_cr && in_cr0)
			sem_post(&sem);

		in_cr0 = in_cr;

		if(t > 0){
			// detete old charcter
			gotoxy(prevx, prevy);
			putchar(' ');
		}

		// draw charcter at the new coordinate
		gotoxy(x, y);
		putchar(mc.c);
		fflush(stdout);

		MySleep(mc.update_freq);
	}

	MySleep(mc.update_freq);

	// delete the last character
	gotoxy(x, y);
	putchar(' ');
	fflush(stdout);

	return NULL;
}

int PointInRect(Rect *r, int x, int y)
{
	if(x >= r->left && x <= r->right && y >= r->top && y <= r->bottom)
		return TRUE;
	else
		return FALSE;
}

