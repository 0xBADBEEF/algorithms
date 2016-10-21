#include <stdio.h>

/* Wave (Lee) Algotithm implementation.
 * Emtpy fields should be -1, all other negatives - "walls".
 * Can be made with stack to avoid to deep recursion. */

enum {
	EF = -1, /* Empty Field */
	W = -100, /* Wall */
	WIDTH = 12,
	HEIGHT = 8,
};

struct coord_t {
	int x;
	int y;
};


int field[HEIGHT][WIDTH] = {
	{EF, EF, W, EF, EF, EF, EF, EF, EF, EF, EF, EF},
	{EF, EF, W, EF, EF, EF, EF, EF, EF, EF, EF, EF},
	{EF, EF, EF, EF, EF, EF, EF, EF, EF, EF, EF, EF},
	{EF, EF, EF, EF, EF, EF, EF, EF, W, W, EF, EF},
	{EF, W, W, W, W, EF, EF, EF, EF, EF, EF, EF},
	{EF, EF, EF, EF, EF, EF, EF, EF, EF, W, W, EF},
	{EF, EF, EF, EF, EF, EF, EF, EF, EF, W, W, EF},
	{EF, EF, EF, EF, EF, EF, EF, EF, EF, EF, EF, EF},
};

struct coord_t path[HEIGHT * WIDTH];
int path_ind = 0;


static int fill_neighbor_diag(int x, int y, int cur)
{
	// x - 1, y - 1
	if (x > 0 && y > 0 && (field[y - 1][x - 1] == EF || field[y - 1][x - 1] > cur + 1))  {
		field[y - 1][x - 1] = cur + 1;
		fill_neighbor_diag(x - 1, y - 1, cur + 1);
	}

	// x + 1, y - 1
	if (x < WIDTH - 1 && y > 0 && (field[y - 1][x + 1] == EF || field[y - 1][x + 1] > cur + 1)) {
		field[y - 1][x + 1] = cur + 1;
		fill_neighbor_diag(x + 1, y - 1, cur + 1);
	}

	// x - 1, y + 1
	if (x > 0 && y < HEIGHT - 1 && (field[y + 1][x - 1] == EF || field[y + 1][x - 1] > cur + 1)) {
		field[y + 1][x - 1] = cur + 1;
		fill_neighbor_diag(x - 1, y + 1, cur + 1);
	}

	// x + 1, y + 1
	if (x < WIDTH - 1 && y < HEIGHT - 1 && (field[y + 1][x + 1] == EF || field[y + 1][x+ 1] > cur + 1)) {
		field[y + 1][x + 1] = cur + 1;
		fill_neighbor_diag(x + 1, y + 1, cur + 1);
	}



	// x, y - 1
	if (y > 0 && (field[y - 1][x] == EF || field[y - 1][x] > cur + 1)) {
		field[y - 1][x] = cur + 1;
		fill_neighbor_diag(x, y - 1, cur + 1);
	}

	// x - 1, y
	if (x > 0 && (field[y][x - 1] == EF || field[y][x - 1] > cur + 1)) {
		field[y][x - 1] = cur + 1;
		fill_neighbor_diag(x - 1, y, cur + 1);
	}

	// x + 1, y
	if (x < WIDTH - 1 && (field[y][x + 1] == EF || field[y][x + 1] > cur + 1)) {
		field[y][x + 1] = cur + 1;
		fill_neighbor_diag(x + 1, y, cur + 1);
	}

	// x, y + 1
	if (y < HEIGHT - 1 && (field[y + 1][x] == EF || field[y + 1][x] > cur + 1)) {
		field[y + 1][x] = cur + 1;
		fill_neighbor_diag(x, y + 1, cur + 1);
	}
}

static void fill_neighbor_cross(int x, int y, int cur)
{
	// x, y - 1
	if (y > 0 && (field[y - 1][x] == EF || field[y - 1][x] > cur + 1)) {
		field[y - 1][x] = cur + 1;
		fill_neighbor_cross(x, y - 1, cur + 1);
	}

	// x - 1, y
	if (x > 0 && (field[y][x - 1] == EF || field[y][x - 1] > cur + 1)) {
		field[y][x - 1] = cur + 1;
		fill_neighbor_cross(x - 1, y, cur + 1);
	}

	// x + 1, y
	if (x < WIDTH - 1 && (field[y][x + 1] == EF || field[y][x + 1] > cur + 1)) {
		field[y][x + 1] = cur + 1;
		fill_neighbor_cross(x + 1, y, cur + 1);
	}

	// x, y + 1
	if (y < HEIGHT - 1 && (field[y + 1][x] == EF || field[y + 1][x] > cur + 1)) {
		field[y + 1][x] = cur + 1;
		fill_neighbor_cross(x, y + 1, cur + 1);
	}
}

static void get_next_step_diag(int x, int y, int cur)
{
	int smallest = cur;
	int next_x, next_y;

	printf("--- next step cur %d\n", cur);

	path[path_ind].x = x;
	path[path_ind].y = y;
	path_ind++;

	if (cur == 0)
		return;

	// x - 1, y - 1
	if (y > 0 && x > 0 && field[y - 1][x - 1] < smallest && field[y - 1][x - 1] >= 0) {
		smallest = field[y - 1][x - 1];
		next_x = x - 1;
		next_y = y - 1;
	}

	// x + 1, y - 1
	if (y > 0 && x < WIDTH - 1 && field[y - 1][x + 1] < smallest && field[y - 1][x + 1] >= 0) {
		smallest = field[y - 1][x + 1];
		next_x = x + 1;
		next_y = y - 1;
	}

	// x - 1, y + 1
	if (y < HEIGHT - 1 && x > 0 && field[y + 1][x - 1] < smallest && field[y + 1][x - 1] >= 0) {
		smallest = field[y + 1][x - 1];
		next_x = x - 1;
		next_y = y + 1;
	}

	// x + 1, y + 1
	if (y < HEIGHT - 1 && x < WIDTH - 1 && field[y + 1][x + 1] < smallest && field [y + 1][x + 1] >= 0) {
		smallest = field[y + 1][x + 1];
		next_x = x + 1;
		next_y = y + 1;
	}



	// x, y - 1
	if (y > 0 && field[y - 1][x] < smallest && field[y - 1][x] >= 0) {
		smallest = field[y - 1][x];
		next_x = x;
		next_y = y - 1;
	}

	// x - 1, y
	if (x > 0 && field[y][x - 1] < smallest && field[y][x - 1] >= 0) {
		smallest = field[y][x - 1];
		next_x = x - 1;
		next_y = y;
	}

	// x + 1, y
	if (x < WIDTH - 1 && field[y][x + 1] < smallest && field[y][x + 1] >= 0) {
		smallest = field[y][x + 1];
		next_x = x + 1;
		next_y = y;
	}

	// x, y + 1
	if (y < HEIGHT - 1 &&field[y + 1][x] < smallest && field[y + 1][x] >= 0) {
		smallest = field[y + 1][x];
		next_x = x;
		next_y = y + 1;
	}

	get_next_step_diag(next_x, next_y, smallest);
}

static void get_next_step_cross(int x, int y, int cur)
{
	int smallest = cur;
	int next_x, next_y;

	path[path_ind].x = x;
	path[path_ind].y = y;
	path_ind++;

	if (cur == 0)
		return;

	// x, y - 1
	if (y > 0 && field[y - 1][x] < smallest && field[y - 1][x] >= 0) {
		smallest = field[y - 1][x];
		next_x = x;
		next_y = y - 1;
	}

	// x - 1, y
	if (x > 0 && field[y][x - 1] < smallest && field[y][x - 1] >= 0) {
		smallest = field[y][x - 1];
		next_x = x - 1;
		next_y = y;
	}

	// x + 1, y
	if (x < WIDTH - 1 && field[y][x + 1] < smallest && field[y][x + 1] >= 0) {
		smallest = field[y][x + 1];
		next_x = x + 1;
		next_y = y;
	}

	// x, y + 1
	if (y < HEIGHT - 1 &&field[y + 1][x] < smallest && field[y + 1][x] >= 0) {
		smallest = field[y + 1][x];
		next_x = x;
		next_y = y + 1;
	}

	get_next_step_cross(next_x, next_y, smallest);
}

void wave(int startx, int starty, int endx, int endy)
{
	int current = 0;
	int checked;

	field[endy][endx] = current;

	// Mark wave
	fill_neighbor_diag(endx, endy, current);

	// Backtrace
	get_next_step_diag(startx, starty, field[starty][startx]);
}


int main(void)
{
	int i;
	int j;

	// Init path
	for (i = 0; i < HEIGHT * WIDTH; i++) {
		path[i].x = -1;
		path[i].y = -1;
	}

	wave(3, 6, 3, 0);

	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			printf("%d ", field[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < HEIGHT * WIDTH; i++) {
		if (path[i].x == -1)
			break;
		printf("(%d, %d) ", path[i].x, path[i].y);
	}
	printf("\n");
}
