#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/* Queue implementation with static memory 
 * push - put element to back
 * pop - get element from front
 * empty - is queue empty?
 * size - occupied elements
 * front - get front element (it stays in queue)
 * back - get back element (it stays in queue)
 */


#define MAX_ELEMENTS            10

struct queue_el {
	struct queue_el *next;
	struct queue_el *prev;          /* Can be removed */
	char state;                     /* 0 - unused, 1 - used */
	void *data;                     /* Should be replaced with real data */
};

struct queue_el queue_array[MAX_ELEMENTS];

struct queue_el *front_el;
struct queue_el *back_el;

int curr_size = 0;

void push(void *data)
{
	int i;
	struct queue_el *new;

	/* Start from currently occupied cell - some optimization */
	for (i = curr_size; i < MAX_ELEMENTS; i++) {
		new = &queue_array[i];
		if (new->state == 0)
			goto found;
	}

	/* Not found from the end - start from the beginning */
	for (i = 0; i < curr_size; i++) {
		new = &queue_array[i];
		if (new->state == 0)
			goto found;
	}

	/* Empty not found */
	return;

found:
	new->data = data;
	new->state = 1;
	new->next = back_el;

	if (back_el != NULL)
		back_el->prev = new;
	back_el = new;
	new->prev = NULL;

	if (front_el == NULL)
		front_el = new;

	curr_size++;
}

void *pop(void)
{
	void *data;

	if (front_el == NULL)
		return NULL;

	data = front_el->data;

	front_el->state = 0;
	curr_size--;

	if (front_el == back_el) {
		front_el = NULL;
		back_el = NULL;
		return data;
	}

/* This is for two linked list */
	front_el = front_el->prev;

/* This is for one linked list */
//	{
//		int i;
//		struct queue_el *tmp;
//
//		tmp = back_el;
//		for (i = 0; i < MAX_ELEMENTS; i++) {
//			if (tmp->next == front_el)
//				break;
//		}
//		front_el = tmp;
//	}

	if (front_el != NULL)
		front_el->next = NULL;

	return data;
}

/* 1 - empty, 0 - non empty */
int empty(void)
{
	if (front_el == NULL)
		return 1;

	return 0;
}

int size(void)
{
	return curr_size;
}

/* Returns next popped element */
void *front(void)
{
	return front_el->data;
}

/* Returns latest came element */
void *back(void)
{
	return back_el->data;
}

void init(void)
{
	int i;

	front_el = NULL;
	back_el = NULL;

	for (i = 0; i < MAX_ELEMENTS; i++) {
		queue_array[i].next = NULL;
		queue_array[i].prev = NULL;
		queue_array[i].state = 0;
		queue_array[i].data = NULL;
	}
}


int main(void)
{
	unsigned long tmp_data;
	int i;

	srand(time(NULL));

	for (i = 0; i < 11; i++) {
		tmp_data = rand(); 
		push((void *)tmp_data);
		printf("--- push %d\n", tmp_data);
	}

	for (i = 0; i < 5; i++) {
		tmp_data = (unsigned long)pop();
		printf("-- pop %d\n", tmp_data);
	}


	for (i = 0; i < 11; i++) {
		tmp_data = rand(); 
		push((void *)tmp_data);
		printf("--- push %d\n", tmp_data);
	}

	for (i = 0; i < 11; i++) {
		tmp_data = (unsigned long)pop();
		printf("-- pop %d\n", tmp_data);
	}

	return 0;
}
