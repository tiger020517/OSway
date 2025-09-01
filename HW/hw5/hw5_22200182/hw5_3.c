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
sem_t	sem;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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
	if(sem_init(&sem, 0, 5))
	{
		perror("Semaphore Error!");
		exit(1);
	}



	// TO DO: create producer thread
	pthread_t tidp = 0;
	pthread_attr_t attrp;
	pthread_attr_init(&attrp);
	pthread_create(&tidp, &attrp, Producer, &q);


	sleep((BUFFER_SIZE + 1) / 2);

	// TO DO: create consumer thread
	pthread_t tidc = 0;
	pthread_attr_t attrc;
	pthread_attr_init(&attrc);
	pthread_create(&tidc, &attrc, Consumer, &q);



	sleep(30);				// wait for 30 sec
	cont = FALSE;

	// TO DO: wait for the producer and the consumer
	pthread_join(tidp, NULL);
	pthread_join(tidc, NULL);

	// TO DO: destroy semaphores and the mutex
	sem_destroy(&sem);
	pthread_mutex_destroy(&mutex);


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
	int	idx;
	StringQueue *q = (StringQueue *)vparam;

	while(cont){
		// TO DO: choose a random number idx in range [0, no_mesg)
		//		  message[idx] is the message to insert
		idx = rand() % no_mesg;


		// TO DO: implement entry section
		sem_wait(&sem);
		pthread_mutex_lock(&mutex);

		// TO DO: insert message[idx] into the queue and display the queue
		Queue_Insert(q, message[idx]);
		Queue_Display(q, screen_width, screen_height);
		// TO DO: implement exit section
		pthread_mutex_unlock(&mutex);

		// TO DO: wait for q->prod_interval seconds
		sleep(q->prod_interval);
	}

	return NULL;
}

void* Consumer(void *vparam)
{
	StringQueue *q = (StringQueue *)vparam;
	char buffer[128] = "";

	while(cont){
		// TO DO: implement entry section
		pthread_mutex_lock(&mutex);

		// TO DO: delete a message from the queue in buffer
		if (q->count > 0)
		{
			Queue_Delete(q, buffer);
			sem_post(&sem);
		}
		else
		{
			pthread_mutex_unlock(&mutex);
			sleep(q->cons_interval);
			continue ;
		}
		// TO DO: implement exit section
		pthread_mutex_unlock(&mutex);

		// TO DO: if deletion was successful, display the output message at coordinate (1, 1)
		//		  then, display the queue
		if(*(buffer))
		{
			gotoxy(1, 1);
			printf("%s", buffer);
			fflush(stdout);
			Queue_Display(q, screen_width, screen_height);
		}

		// TO DO: wait fir q->cons_interval seconds
		sleep(q->cons_interval);

	}

	return NULL;
}

