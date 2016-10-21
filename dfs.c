#include <stdio.h>

enum {
	GRAPH_VERTICES = 10,
};

/* Non-recoursive implementation of Depth-First Search algorithm */

struct stack_el {
	int node;
	int parent;
};

struct stack_el stack[GRAPH_VERTICES];
int discovered[GRAPH_VERTICES];
int cur_stack = -1;

void stack_push(int vert, int parent)
{
	cur_stack++;
	stack[cur_stack].node = vert;
	stack[cur_stack].parent = parent;
}

void stack_pop(int *vertp, int *parentp)
{
	int tmp;

	if (cur_stack < 0) {
		*vertp = -1;
		*parentp = -1;
		return ;
	}

	*vertp = stack[cur_stack].node;
	*parentp = stack[cur_stack].parent;

	stack[cur_stack].node = -1;
	stack[cur_stack].parent = -1;
	cur_stack--;
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
	int parent;
	int child;
	int i;
	int verts = 0;

	stack_push(start, start);

	while(!stack_empty()) {

		stack_pop(&node, &parent);

		if (discovered[node] == -1) {
			discovered[node] = parent;

			if (node == end)
				goto find_path;

			i = 0;
			do {
				if (i >= GRAPH_VERTICES)
					break;

				child = adjustment_list[node][i];

				if (child == -1)
					break;

				if (discovered[child] == -1)
					stack_push(child, node);

				i++;
			} while (1);
		}
	}

	return 0;

	// Algorithm itself ends here, now it si path search
find_path:
	node = end;
	parent = discovered[end];

	for (i = 0; i < GRAPH_VERTICES; i++) {
		// Beginning is its parent itself
		// Workaround if start = end
		if (node == parent && i > 0)
			break;

		path[i] = node;
		verts++;

		parent = node;
		node = discovered[node];
	}

	return verts;
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
		stack[i].node = -1;
		stack[i].parent = -1;
		discovered[i] = -1;
	}

	ret = dfs(adjustment_list, path, 0, 8);

	printf("%d\n", ret);

	for (i = 0; i < ret; i++) {
		printf("-- %d\n", path[i]);
	}

	return 0;
}
