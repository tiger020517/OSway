// DO NOT MODIFY THIS FILE

#ifndef	__STRING_QUEUE__
#define	__STRING_QUEUE__

#define BUFFER_SIZE 5
typedef struct {
	char *data[BUFFER_SIZE];
	int in, out;
	int count;

	int prod_interval, cons_interval;
} StringQueue;


void Queue_Init(StringQueue *q, int prod_interval, int cons_interval);
int Queue_Insert(StringQueue *q, char str[]);
int Queue_Delete(StringQueue *q, char str[]);
void Queue_Display(StringQueue *q, int screen_width, int screen_height);

#ifdef	_DEBUG
void Queue_Test(StringQueue *q);
#endif	//	_DEBUG

#endif	//	__STRING_QUEUE__

