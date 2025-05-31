/***
	
	compilation:
		gcc hw4_3.c Console.c -D SYNCHRONIZE -o hw4_3_sync
		gcc hw4_3.c Console.c -o hw4_3_no_sync

***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <pthread.h>

#include "Console.h"

//#define SYNCHRONIZE

#define TRUE 1
#define FALSE 0

#define MIN(x, y) ((x) <= (y) ? (x) : (y))
#define MAX(x, y) ((x) >= (y) ? (x) : (y))

#define ESC 27

#define DRAW 1
#define ERASE 0

int home_x = 1, home_y = 1;

typedef struct {
	int x, y;
	int dx, dy;
	int width;			// the width of the fighter

	int max_x, max_y;		// the width and height of screen
} Fighter;

void DisplayFighter(Fighter *f);

int DrawFighter(Fighter *f, int erase);
int Clip(int *x, int *y, int width, int height, int left, int top, int right, int bottom);
void LaunchMissile(Fighter *f, int height);

typedef struct {
	char warhead;           // the character that will be printed at the head coordinate

	float x, y;				// current position of missile head
	float dx, dy;			// direction of movement
	int height;				// the height of the missile

	int max_x, max_y;		// the width and height of screen

	pthread_t tid;			// the id of the thread that moves the missile
} Missile;

void* MoveMissile(void *vparam);
int DrawMissile(Missile *m, int erase);

int main()
{
	srand(time(NULL));

	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	home_x = 1;
	home_y = screen_height + 1;

	clrscr();

	Fighter f = { screen_width / 2, screen_height / 2, 0, 0, 5, screen_width, screen_height };

#ifdef	_DEBUG
	DisplayFighter(&f);
	MyPause(NULL);
#endif	//	_DEBUG

	DrawFighter(&f, DRAW);
	int cont = TRUE;
	for(int t = 0; cont; t++){
		if(t < 0)						// overflow
			t = 0;

		if(kbhit()){
			int k = getch();
			switch(k){
			case 'j':
			case 'a':
				f.dx = MAX(-3, ((f.dx < 0) ? f.dx - 1 : -1));
				f.dy = 0;
				break;

			case 'l':
			case 'd':
				f.dx = MIN(3, ((f.dx > 0) ? f.dx + 1 : 1));
				f.dy = 0;
				break;

			case 'i':
			case 'w':
				f.dy = MAX(-3, ((f.dy < 0) ? f.dy - 1 : -1));
				f.dx = 0;
				break;

			case 'k':
			case 's':
				f.dy = MIN(3, ((f.dy > 0) ? f.dy + 1 : 1));
				f.dx = 0;
				break;

			case ' ':
				LaunchMissile(&f, 2);
				break;

			case ESC:
				cont = FALSE;
				break;

			default:
				f.dx = f.dy = 0;
				break;
			}
		}
	
		if(cont == FALSE)
			break;

		if((t % 5 == 0) && (f.dx != 0 || f.dy != 0)){
			DrawFighter(&f, ERASE);

			f.x += f.dx;
			f.y += f.dy;
			
			int clipped = Clip(&f.x, &f.y, f.width, 1, 1, 1, screen_width, screen_height);
			if(clipped)
				f.dx = f.dy = 0;

			DrawFighter(&f, DRAW);
		}

#ifdef	SYNCHRONIZE
		LockDisplay();
#endif	// SYNCHRONIZE
		gotoxy(home_x, home_y);
		fflush(stdout);
#ifdef	SYNCHRONIZE
		UnlockDisplay();
#endif	//	SYNCHRONIZE

		MySleep(10);
	}

	gotoxy(1, screen_height);
	printf("Bye!\n");
	fflush(stdout);

	return 0;
}

int Clip(int *x, int *y, int width, int height, int left, int top, int right, int bottom)
{
	int clipped = FALSE;

	if(*x < left){
		*x = left;
		clipped = TRUE;
	}

	if(*x > right - width + 1){
		*x = right - width + 1;
		clipped = TRUE;
	}

	if(*y < top){
		*y = top;
		clipped = TRUE;
	}

	if(*y > bottom - height + 1){
		*y = bottom - height + 1;
		clipped = TRUE;
	}

	return clipped;
}

void DisplayFighter(Fighter *f)
{
	printf("x, y = %d, %d\n", f->x, f->y);
	printf("dx, dy = %d, %d\n", f->dx, f->dy);
	printf("width = %d\n", f->width);
	printf("max_x, max_y = %d, %d\n", f->max_x, f->max_y);
}

int DrawFighter(Fighter *f, int flag)
{
	if(f->x < 1 || f->x + f->width - 1  > f->max_x || f->y < 1 || f->y > f->max_y)
		return FALSE;

#ifdef	SYNCHRONIZE
	LockDisplay();
#endif	//	SYNCHRONIZE

	if(flag == DRAW){
		gotoxy(f->x, f->y);
		putchar('<');
		for(int i = 1; i < f->width / 2; i++)
			putchar('-');
		putchar('A');
		for(int i = 1; i < f->width / 2; i++)
			putchar('-');
		putchar('>');
	} else {
		gotoxy(f->x, f->y);
		for(int i = 0; i < f->width; i++)
			putchar(' ');
	}

	gotoxy(home_x, home_y);
	fflush(stdout);

#ifdef	SYNCHRONIZE
	UnlockDisplay();
#endif	//	SYNCHRONIZE

	return TRUE;
}

void LaunchMissile(Fighter *f, int height)
{
	static char warheads[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
	int no_warheads = strlen(warheads);

	Missile *m = NULL;
	// TO DO: dynamically allocate memory for a missile instance
	//		  on failure, display an error message at (home_x, home_y) using PrintXY (see Console.c) and return
	m = (Missile *)malloc(sizeof(Missile));
	if(!m){
		PrintXY(home_x, home_y, "Error: out of memory");
		return;
	}
	m->warhead = warheads[rand() % no_warheads];
	m->x = f->x + f->width / 2;
	m->y = f->y - height;
	m->dx = f->dx / 2.F;
	m->dy = -1;
	m->height = height;
	m->max_x = f->max_x;
	m->max_y = f->max_y;
	m->tid = 0;					// for safety

	// TO DO: create a thread to animate the missile
	//		  receive the tid of the child thread in m->tid
	pthread_create(&m->tid, NULL, MoveMissile, (void *)m);
}

void* MoveMissile(void *vparam)
// TO DO: reuse the MoveMissile() you wrote for hw4_2
//		e.g., save the body of MovileMissile() in hw4_2.c to a file 'block' using the command ":<start_line>,<end_line> w! block"
//			  and then, read it below using ":r block"
{
	// TO DO: copy and paste your solution to hw4_2
Missile *m = (Missile *)vparam;

	// TO DO: draw missile by calling DrawMissile()
	DrawMissile(m, DRAW);

	while(1){
		// TO DO: erase missile (call DrawMissile() passing ERASE as the flag)
		DrawMissile(m, ERASE);

		// TO DO: move missile by adding (dx, dy) to (x, y)
		m->x += m->dx;
		m->y += m->dy;

		// TO DO: draw missile
		//		  if the return value of DrawMissile() is FALSE, break the loop
		if(DrawMissile(m, DRAW) == FALSE)
			break;


#ifdef	 SYNCHRONIZE
		LockDisplay();
#endif	// SYNCHRONIZE
		gotoxy(home_x, home_y);
		fflush(stdout);
#ifdef SYNCHRONIZE
		UnlockDisplay();
#endif	// SYNCHRONIZE


		MySleep(50);
	}

	// TO DO: [IMPORTANT] deallocate m (m reached the top)
	free(m);
	return NULL;
}

int DrawMissile(Missile *m, int flag)
// TO DO: read this function carefuly and fully understand the techniques used for it
{
	if(m->x < 1 || m->x > m->max_x || m->y < 1 || m->y + m->height - 1 > m->max_y)
		return FALSE;

#ifdef	SYNCHRONIZE
	LockDisplay();
#endif	//	SYNCHRONIZE

	for(int i = 0; i < m->height; i++){
		gotoxy((int)(m->x + 0.5F), (int)(m->y + i + 0.5F));
		if(flag == DRAW)
			putchar((i == 0) ? m->warhead : '|');
		else
			putchar(' ');
	}

	gotoxy(home_x, home_y);
	fflush(stdout);

#ifdef	SYNCHRONIZE
	UnlockDisplay();
#endif	//	SYNCHRONIZE

	return TRUE;
}

