#include <stdio.h>

enum {
	GRAPH_VERTICES = 10,
};


int visited[GRAPH_VERTICES] = {-1};
int queue[GRAPH_VERTICES] = {-1};
int write_ind = -1;
int read_ind = -1;

static inline void queue_push(int node)
{
	write_ind++;
	queue[write_ind] = node;
}

static inline int queue_pop(void)
{
	int node;

	read_ind++;

	if (read_ind > write_ind)
		return -1;

	node = queue[read_ind];
	queue[read_ind] = -1;

	return node;
}

static inline int queue_empty(void)
{
	if (read_ind == write_ind)
		return 1;

	return 0;
}

int get_path(int target_id, int path[GRAPH_VERTICES])
{
	int i = 0;
	int next_node = 0;
	int steps = 0;

	next_node = target_id;
	do {
		path[i] = next_node;
		i++;
		steps++;
		if (visited[next_node] == next_node) 		// parent equal to child - top of the top 
			break;

		next_node = visited[next_node];
	} while (1);

	return steps;
}

int bfs(int adjustment_list[GRAPH_VERTICES][GRAPH_VERTICES], int path[GRAPH_VERTICES], int start_id, int target_id)
{
	int node;
	int steps = 0;
	int child = 0;
	int i;

	queue_push(start_id);

	visited[start_id] = start_id; 					// parent of the start is the start itself
	while (!queue_empty()) {
		node = queue_pop();
		steps++;

		if (node == target_id)
			return get_path(target_id, path);

		i = 0;
		do {
			child = adjustment_list[node][i];
			i++;

			if (child == -1)
				break;

			if (visited[child] == -1) {
				queue_push(child);
				visited[child] = node;				// save parent
			}
		} while (1);

	}
	return -1;
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
		visited[i] = -1;
		queue[i] = -1;
		path[i] = -1;
	}

	ret = bfs(adjustment_list, path, 0, 8);

	printf("%d\n", ret);

	for (i = 0; i < ret; i++) {
		printf("-- %d\n", path[i]);
	}

	return 0;
}
