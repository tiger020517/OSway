// DO NOT MODIFY THIS FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Console.h"
#include "StringQueue.h"


#define TRUE 1
#define FALSE 0

void Queue_Init(StringQueue *q, int prod_interval, int cons_interval)
{
	q->in = q->out = q->count = 0;
	memset(q->data, 0, sizeof(char *) * BUFFER_SIZE);	// for safety
	q->prod_interval = prod_interval;
	q->cons_interval = cons_interval;
}

int Queue_Insert(StringQueue *q, char str[])
{
	if(q->count >= BUFFER_SIZE){
		gotoxy(1, 2);
		printf("Queue is full!\n");	

		fflush(stdout);

		return FALSE;
	}

	char *new_str = (char *)malloc(strlen(str) + 1);
	if(new_str == NULL){
		printf("Failed to allocate memory in line %d\n", __LINE__);
		exit(-1);
	}
	strcpy(new_str, str);

	q->data[q->in] = new_str;
	q->in = (q->in + 1) % BUFFER_SIZE;
	q->count++;

	return TRUE;
}

int Queue_Delete(StringQueue *q, char str[])
{
	if(q->count <= 0){
		gotoxy(1, 3);
		printf("Queue is empty!\n");
		fflush(stdout);

		return FALSE;
	}

	strcpy(str, q->data[q->out]);
	free(q->data[q->out]);
	q->data[q->out] = NULL;			// for safety

	q->out = (q->out + 1) % BUFFER_SIZE;
	q->count--;

	return TRUE;
}

void Queue_Display(StringQueue *q, int screen_width, int screen_height)
{
	int y0 = (screen_height - BUFFER_SIZE) / 2;

	int p = q->out;

	// display count
	char message[256] = "";
	sprintf(message, "   count = %d   \n",  q->count);
	gotoxy((screen_width - strlen(message)) / 2, y0 - 1);
	printf("%s", message);

	// display contents
	for(int i = 0; i < BUFFER_SIZE; i++){
		int sy = y0 + i;

		// clear the row
		gotoxy(1, sy);
		for(int j = 1; j <= screen_width; j++)
			putchar(' ');

		if(i < q->count){		// string
			char *str = q->data[p];
			if(str == NULL){		// for safety
				gotoxy(1, 4);
				printf("Something is wrong in %s\n", __FUNCTION__);
				fflush(stdout);

				MyPause(__FUNCTION__);
			} else {
				p = (p + 1) % BUFFER_SIZE;

				int sx = (screen_width - strlen(str)) / 2;
				gotoxy(sx, sy);
				printf("%s", str);
			}
		}
	}

	fflush(stdout);
}

#ifdef	_DEBUG
void Queue_Test(StringQueue *q)
{
	Queue_Insert(q, "Hello.");
	Queue_Insert(q, "Nice to see you!");
	Queue_Insert(q, "Good morning.");

	Queue_Display(q, screen_width, screen_height);
	gotoxy(1, 1);
	MyPause("");


	char temp[256] = "";

	while(q->count > 0){
		Queue_Delete(q, temp);
		Queue_Display(q, screen_width, screen_height);

		gotoxy(1, 1);
		printf("Deleted string: [%s]\n", temp);
		fflush(stdout);

		MyPause("");
	}
	
	Queue_Insert(q, "Nice to see you, again!");
	Queue_Insert(q, "Nice to see you, again!");
	Queue_Insert(q, "Nice to see you, again!");

	Queue_Display(q, screen_width, screen_height);
	gotoxy(1, 1);
	MyPause("");
}
#endif	//	_DEBUG

