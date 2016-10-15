#include <stdio.h>

enum {
	GRAPH_VERTICES = 10,
};



int bfs(int[][] adjustment_list, int start_id, int target_id, int *path_list)
{

}


int main(void)
{
	int adjustment_list[GRAPH_VERTICES][GRAPH_VERTICES] = {
		{1, 3, 				0, 0, 0, 0, 0, 0, 0, 0},
		{0, 2, 5, 6, 7, 9,  0, 0, 0, 0},
		{1, 4, 9, 			0, 0, 0, 0, 0, 0, 0},
		{0, 9, 				0, 0, 0, 0, 0, 0, 0, 0},
		{2, 9, 				0, 0, 0, 0, 0, 0, 0, 0},
		{1, 8,              0, 0, 0, 0, 0, 0, 0, 0},
		{1, 				0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 				0, 0, 0, 0, 0, 0, 0, 0, 0},
		{5, 9, 				0, 0, 0, 0, 0, 0, 0, 0},
		{1, 2, 3, 4, 8, 	0, 0, 0, 0, 0, 0},
	};
	int shortest_path[GRAPH_VERTICES] = {0};
	int ret;

}