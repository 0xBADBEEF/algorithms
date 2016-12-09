#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/* Stack implementation with static memory */

#define MAX_ELEMENTS            10

struct stack_el {
	struct stack_el *prev;
	char state;		     /* 0 - unused, 1 - used */
	void *data;		     /* Should be replaced with real data */
};

struct stack_el stack_array[MAX_ELEMENTS];

struct stack_el *top_el;

int curr_size = 0;


void push(void *data)
{
	int i;
	struct stack_el *new;

	/* Start from currently occupied cell - some optimization */
	for (i = curr_size; i < MAX_ELEMENTS; i++) {
		new = &stack_array[i];
		if (new->state == 0)
			goto found;
	}

	/* Not found from the end - start from the beginning */
	for (i = 0; i < curr_size; i++) {
		new = &stack_array[i];
		if (new->state == 0)
			goto found;
	}

	return;

found:
	new->data = data;
	new->state = 1;
	new->prev = top_el;

	top_el = new;
	curr_size++;
}

void *pop(void)
{
	void *data;

	if (top_el == NULL)
		return NULL;

	data = top_el->data;
	top_el->state = 0;
	curr_size--;
	top_el = top_el->prev;

	return data;
}

void *top(void)
{
	return top_el->data;
}

int empty(void)
{
	if (curr_size == 0)
		return 1;

	return 0;
}

int size(void)
{
	return curr_size;
}

void init(void)
{
	int i;

	top_el = NULL;
	for (i = 0; i < MAX_ELEMENTS; i++) {
		stack_array[i].prev = NULL;
		stack_array[i].state = 0;
		stack_array[i].data = NULL;
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
