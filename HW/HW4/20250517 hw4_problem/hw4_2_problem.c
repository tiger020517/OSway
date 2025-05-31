/***
	
	compilation:
		gcc hw4_2.c Console.c -D SYNCHRONIZE -o hw4_2_sync
		gcc hw4_2.c Console.c -o hw4_2_no_sync

***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int home_x = 1, home_y = 1;	// the coordinates to place the cursor

typedef struct {
	char warhead;			// the character that will be printed at the head coordinates

	float x, y;				// current position of missile head
	float dx, dy;			// the direction of movement
	int height;				// the height of the missile

	int max_x, max_y;		// the width and height of the screen

	pthread_t tid;			// the id of the thread that animates the missile
} Missile;

void* MoveMissile(void *vparam);
int DrawMissile(Missile *m, int erase);

int main()
{
	static char key_list[] = "asdfghjkl;\'";
	int no_key = strlen(key_list);

	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	home_x = 1;
	home_y = screen_height + 1;

	clrscr();

	while(TRUE){
		if(kbhit()){
			int k = getch();
			if(k == ESC)
				break;

			char *p = strchr(key_list, k);
			if(p){							// the input key is in key_list
				int idx = p - key_list;		// the input is the idx-th character of key_list

				Missile *m = NULL;
				// TO DO: dynamically allocate memory for a Missile instance
				//		  on failure, display an error message at (home_x, home_y) by calling PrintXY() (see Console.c)
				m = (Missile *)malloc(sizeof(Missile));
				if(m == NULL){
					PrintXY(home_x, home_y, "Error: out of memory");
					continue;
				}

	
				m->warhead = k;
				m->x = screen_width * (idx + 1) / (no_key + 1);
				m->y = screen_height - 2;
				m->dx = 0;
				m->dy = -1;
				m->height = 2;
				m->max_x = screen_width;
				m->max_y = screen_height;
				m->tid = 0;					// for safety

				// TO DO: create a thread using MoveMissile() and m
				pthread_create(&m->tid, NULL, MoveMissile, (void *)m);

			} else if(k == ' '){			// the input key is space
				// TO DO: create a number of threads equal to no_key to animate all charcters in key_list
				//		  set the warhead character to '^'

				for(int i = 0; i < no_key; i++){
					Missile *m = NULL;
					m = (Missile *)malloc(sizeof(Missile));
					if(m == NULL){
						PrintXY(home_x, home_y, "Error: out of memory");
						continue;
					}

					m->warhead = '^';
					m->x = screen_width * (i + 1) / (no_key + 1);
					m->y = screen_height - 2;
					m->dx = 0;
					m->dy = -1;
					m->height = 2;
					m->max_x = screen_width;
					m->max_y = screen_height;
					m->tid = 0;

					pthread_create(&m->tid, NULL, MoveMissile, (void *)m);
				}
			}
		}
	
#ifdef SYNCHRONIZE
		LockDisplay();
#endif	// SYNCHRONIZE
		gotoxy(home_x, home_y);
		fflush(stdout);
#ifdef SYNCHRONIZE
		UnlockDisplay();
#endif	// SYNCHRONIZE

		MySleep(10);
	}

	gotoxy(1, screen_height);
	printf("Bye!\n");
	fflush(stdout);

	return 0;
}

void* MoveMissile(void *vparam)
// TO DO: read this function carefuly and fully understand the techniques used for it
{
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
	// check if the missile went out of the screen
	if(m->x < 1 || m->x > m->max_x || m->y < 1 || m->y + m->height - 1 > m->max_y)
		return FALSE;

#ifdef	 SYNCHRONIZE
	LockDisplay();
#endif	//	 SYNCHRONIZE

	for(int i = 0; i < m->height; i++){
		gotoxy((int)(m->x + 0.5F), (int)(m->y + i + 0.5F));
		if(flag == DRAW)
			putchar((i == 0) ? m->warhead : '|');
		else
			putchar(' ');
	}

	gotoxy(home_x, home_y);
	fflush(stdout);

#ifdef	 SYNCHRONIZE
	UnlockDisplay();
#endif	//	 SYNCHRONIZE

	return TRUE;
}

