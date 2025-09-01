/*

	compilation:
		gcc hw5_3.c StringQueue.c Console.c -o hw5_3

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <pthread.h>

#include <semaphore.h>


#include "Console.h"
#include "StringQueue.h"


#define TRUE 1
#define FALSE 0

#define ESC 27

int screen_width = 0;
int screen_height = 0;

int cont = TRUE;

// TO DO: declare semaphores and a mutex


void* Producer(void *vparam);
void* Consumer(void *vparam);

int main(int argc, char *argv[])
{
	if(argc < 3){
		printf("Usage: %s <prod_interval> <cons_interval>\n", argv[0]);
		exit(0);
	}

	screen_width = getWindowWidth();
	screen_height = getWindowHeight() - 3;

	clrscr();

	int prod_interval = atoi(argv[1]);
	if(prod_interval == 0)
		prod_interval = 1;

	int cons_interval = atoi(argv[2]);
	if(cons_interval == 0)
		cons_interval = 1;

	StringQueue q;
	Queue_Init(&q, prod_interval, cons_interval);

	// TO DO: initialize semaphores and mutex



	// TO DO: create producer thread
	


	sleep((BUFFER_SIZE + 1) / 2);

	// TO DO: create consumer thread




	sleep(30);				// wait for 30 sec
	cont = FALSE;

	// TO DO: wait for the producer and the consumer


	// TO DO: destroy semaphores and the mutex



	gotoxy(1, screen_height);
	printf("Bye!\n");

	return 0;
}

void* Producer(void *vparam)
{
	const int no_mesg = 10;
	static char message[][256] = {
		"Even the darkest night will end and the sun will rise.",
		"You are stronger than you think, and braver than you feel.",
		"It’s okay to not be okay. Take your time.",
		"Every day is a new beginning. Take a deep breath and start again.",
		"This too shall pass.",
		"You’re not alone. I’m here for you.",
		"Believe in yourself—you’ve made it through before, and you will again.",
		"Your story isn’t over yet.",
		"One small step at a time is still progress.",
		"Keep going. Your future self will thank you."
	};

	StringQueue *q = (StringQueue *)vparam;

	while(cont){
		// TO DO: choose a random number idx in range [0, no_mesg)
		//		  message[idx] is the message to insert


		// TO DO: implement entry section


		// TO DO: insert message[idx] into the queue and display the queue


		// TO DO: implement exit section


		// TO DO: wait for q->prod_interval seconds
	}

	return NULL;
}

void* Consumer(void *vparam)
{
	StringQueue *q = (StringQueue *)vparam;
	char buffer[128] = "";

	while(cont){
		// TO DO: implement entry section


		// TO DO: delete a message from the queue in buffer


		// TO DO: implement exit section


		// TO DO: if deletion was successful, display the output message at coordinate (1, 1)
		//		  then, display the queue



		// TO DO: wait fir q->cons_interval seconds


	}

	return NULL;
}

