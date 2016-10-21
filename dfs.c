#include <stdio.h>

enum {
	GRAPH_VERTICES = 10,
};

/* Non-recoursive implementation of Depth-First Search algorithm */


int stack[GRAPH_VERTICES];
int discovered[GRAPH_VERTICES];
int cur_stack = -1;

void stack_push(int vert)
{
	cur_stack++;
	stack[cur_stack] = vert;
}

int stack_pop(void)
{
	int tmp;

	if (cur_stack < 0)
		return -1;

	tmp = stack[cur_stack];
	stack[cur_stack] = -1;
	cur_stack--;

	return tmp;
}

int stack_empty(void)
{
	if (cur_stack >= 0)
		return 0;

	return 1;
}

int dfs(int adjustment_list[GRAPH_VERTICES][GRAPH_VERTICES], int path[GRAPH_VERTICES], int start, int end)
{
	int node;
	int child;
	int i;

	stack_push(start);

	while(!stack_empty()) {

		node = stack_pop();

		if (discovered[node] == -1) {
			discovered[node] = 1;

			if (node == end)
				return 1;

			i = 0;
			do {
				if (i >= GRAPH_VERTICES)
					break;

				child = adjustment_list[node][i];

				if (child == -1)
					break;

				if (discovered[child] == -1)
					stack_push(child);

				i++;
			} while (1);
		}
	}

	return 0;
}

int main(void)
{
	int adjustment_list[GRAPH_VERTICES][GRAPH_VERTICES] = {
		{1, 3, 				-1, -1, -1, -1, -1, -1, -1, -1},
		{0, 2, 5, 6, 7, 9,  -1, -1, -1, -1},
		{1, 4, 9, 			-1, -1, -1, -1, -1, -1, -1},
		{0, 9, 				-1, -1, -1, -1, -1, -1, -1, -1},
		{2, 9, 				-1, -1, -1, -1, -1, -1, -1, -1},
		{1, 8,              -1, -1, -1, -1, -1, -1, -1, -1},
		{1, 				-1, -1, -1, -1, -1, -1, -1, -1, -1},
		{1, 				-1, -1, -1, -1, -1, -1, -1, -1, -1},
		{5, 9, 				-1, -1, -1, -1, -1, -1, -1, -1},
		{1, 2, 3, 4, 8, 	-1, -1, -1, -1, -1},
	};
	int path[GRAPH_VERTICES] = {-1};
	int ret;
	int i;

	// Init arrays
	for (i = 0; i < GRAPH_VERTICES; i++) {
		stack[i] = -1;
		discovered[i] = -1;
	}

	ret = dfs(adjustment_list, path, 0, 8);

	printf("%d\n", ret);

	return 0;
}
